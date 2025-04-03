#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

#include "hal/gpio.h"
#include "hal/joystick.h"
#include "hal/rotary_statemachine.h"
#include "hal/accelerometer.h"
#include "hal/lcd.h"

#include "sharedDataLayout.h"
#include "GUI_Paint.h"

// General R5 Memomry Sharing Routine
// ----------------------------------------------------------------
#define ATCM_ADDR     0x79000000  // MCU ATCM (p59 TRM)
#define BTCM_ADDR     0x79020000  // MCU BTCM (p59 TRM)
#define MEM_LENGTH    0x8000

// Return the address of the base address of the ATCM memory region for the R5-MCU
volatile void* getR5MmapAddr(void)
{
    // Access /dev/mem to gain access to physical memory (for memory-mapped devices/specialmemory)
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        perror("ERROR: could not open /dev/mem; Did you run with sudo?");
        exit(EXIT_FAILURE);
    }

    // Inside main memory (fd), access the part at offset BTCM_ADDR:
    // (Get points to start of R5 memory after it's memory mapped)
    volatile void* pR5Base = mmap(0, MEM_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BTCM_ADDR);
    if (pR5Base == MAP_FAILED) {
        perror("ERROR: could not map memory");
        exit(EXIT_FAILURE);
    }
    close(fd);

    return pR5Base;
}

void freeR5MmapAddr(volatile void* pR5Base)
{
    if (munmap((void*) pR5Base, MEM_LENGTH)) {
        perror("R5 munmap failed");
        exit(EXIT_FAILURE);
    }
}

// Global flag to allow CTRL+C termination.
volatile bool stop_main_thread = false;

float target_x = -99.9f;
float target_y = 99.9f;

volatile void* pR5Base = NULL;

time_t start_time = 0;
int hit_count = 0;
int miss_count = 0;

bool firing = false;

// External frame buffer allocated in the LCD module.
extern UWORD *s_fb;

void update_screen(void)
{
    // Create a new image in the framebuffer.
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    char hitStr[32];
    char missStr[32];
    char timeStr[32];

    // Prepare the text strings.
    snprintf(hitStr, sizeof(hitStr), "Hits: %d", hit_count);
    snprintf(missStr, sizeof(missStr), "Misses: %d", miss_count);

    // Calculate elapsed time.
    time_t now = time(NULL);
    int elapsed = (int)difftime(now, start_time);
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    snprintf(timeStr, sizeof(timeStr), "Time: %02d:%02d", minutes, seconds);

    // Draw the text strings at chosen positions.
    Paint_DrawString_EN(10, 10, hitStr, &Font20, WHITE, BLACK);
    Paint_DrawString_EN(10, 40, missStr, &Font20, WHITE, BLACK);
    Paint_DrawString_EN(10, 70, timeStr, &Font20, WHITE, BLACK);

    // Finally, update the LCD.
    LCD_1IN54_DisplayWindows(0, 0, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, s_fb);
}

static void pick_random_point(float *x_tgt, float *y_tgt)
{
    float r1 = ((float)rand() / (float)RAND_MAX); // in [0,1]
    float r2 = ((float)rand() / (float)RAND_MAX);
    *x_tgt = (r1 - 0.5f);  // map to [-0.5, +0.5]
    *y_tgt = (r2 - 0.5f);  // map to [-0.5, +0.5]
}

// Signal handler for CTRL+C
void sigint_handler(int signum)
{
    (void)signum;
    stop_main_thread = true;
}

void on_rotary_push_button_down(void)
{
    printf("Fire!");
    if (MEM_UINT8((uint8_t*)pR5Base + FIRING_STATUS_OFFSET) == 0 && !firing) {
        bool in_range = MEM_UINT8((uint8_t*)pR5Base + FIRING_IN_RANGE_OFFSET);
        firing = true;
        
        if (in_range) {
            hit_count++;            
            printf("Hit!\n");

            MEM_UINT8((uint8_t*)pR5Base + FIRING_STATUS_OFFSET) = 1;

            // Prevent hitting at the same target twice.
            target_x = -99.9f;
            target_y = 99.9f;


            // Wait for the animation to finish running (blocking the thread).
            usleep(200000);

            // Pick a new target.
            float new_target_x, new_target_y;
            pick_random_point(&new_target_x, &new_target_y);
            target_x = new_target_x;
            target_y = new_target_y;

            MEM_FLOAT((uint8_t*)pR5Base + X_TARGET_OFFSET) = target_x;
            MEM_FLOAT((uint8_t*)pR5Base + Y_TARGET_OFFSET) = target_y;

            printf("New target: (%.3f, %.3f)\n", new_target_x, new_target_y);
        } else {
            printf("Miss!\n");
            miss_count++;
            MEM_UINT8((uint8_t*)pR5Base + FIRING_STATUS_OFFSET) = 2;

            usleep(450000);
        }
    }

    MEM_UINT8((uint8_t*)pR5Base + FIRING_STATUS_OFFSET) = 0;
    firing = false;

    // Immediately update the LCD with new stats.
    update_screen();
}

void on_joystick_push_button_down(void) 
{
    stop_main_thread = true;
    MEM_UINT8((uint8_t*)pR5Base + TERMINATE_PROGRAM_FLAG_OFFSET) = true;
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Initialize hardware and subsystems.
    Gpio_init();
    Lcd_init();
    Accelerometer_init();
    RotaryStateMachine_init();
    Joystick_init();

    Joystick_register_push_button_down_callback(on_joystick_push_button_down);

    start_time = time(NULL);

    // 2) Randomly pick a target in [-0.5, +0.5]
    float curr_x, curr_y;
    pick_random_point(&target_x, &target_y);
    pR5Base = getR5MmapAddr();
    if (!pR5Base) {
        perror("No R5 memory can be found.");
        return 0;
    }

    MEM_FLOAT((uint8_t*)pR5Base + X_TARGET_OFFSET) = target_x;
    MEM_FLOAT((uint8_t*)pR5Base + Y_TARGET_OFFSET) = target_y;
    MEM_UINT8((uint8_t*)pR5Base + FIRING_STATUS_OFFSET) = 0;

    while (!stop_main_thread) {
        // Block main thread to avoid firing too quickly.
        if (RotaryStateMachine_is_button_down()) {
            on_rotary_push_button_down();

            // Add slight delay to avoid rapid counting.
            usleep(500000);
        }

        update_screen();
        
        curr_x = Accelerometer_get_normalized_x_rotation();
        curr_y = Accelerometer_get_normalized_y_rotation();
        
        printf("Random target: (%.3f, %.3f)\n", target_x, target_y);
        printf("Current: (%.3f, %.3f)\n", curr_x, curr_y);

        MEM_FLOAT((uint8_t*)pR5Base + NORMALIZED_X_ROTATION_OFFSET) = curr_x;
        MEM_FLOAT((uint8_t*)pR5Base + NORMALIZED_Y_ROTATION_OFFSET) = curr_y;

        // sleep(1);
        usleep(100000);
    }
    
    // Cleanup.
    RotaryStateMachine_cleanup();
    Joystick_cleanup();
    Accelerometer_cleanup();
    Lcd_cleanup();
    Gpio_cleanup();

    freeR5MmapAddr(pR5Base);

    return 0;
}