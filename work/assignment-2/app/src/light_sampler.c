#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>  // For nanosleep

#include "hal/gpio.h"
#include "hal/rotary_statemachine.h"
#include "hal/pwm.h"
#include "hal/sampler.h"

#include "lcd.h"
#include "udp.h"
#include "periodTimer.h"

// Create a thread and lock for the LCD updates.
pthread_t lcd_thread;
pthread_mutex_t lcd_lock_thread;

bool stop_main_thread = false;
static bool stop_lcd_thread = false;

void on_clockwise_turned() 
{
    Pwm_increase_frequency();
}

void on_counterclockwise_turned() 
{
    Pwm_decrease_frequency();
}

static void print_light_status(Period_statistics_t *stats)
{
    int size;
    double *history = Sampler_getHistory(&size);
    double smoothed_avg = 0.0;
    // https://en.wikipedia.org/wiki/Exponential_smoothing
    // Compute exponential smoothing of the samples.
    if (size > 0) {
        smoothed_avg = history[0];
        for (int i = 1; i < size; i++) {
            smoothed_avg = 0.1 * history[i] + (1 - 0.1) * smoothed_avg;
        }
    }

    int dips = Sampler_getDips();
    int pwm_freq = Pwm_get_frequency();

    // Line 1: Print fixed-width status values
    // Order: # samples, LED flash frequency, averaged voltage, dips, then jitter info
    printf("#Smpl/s = %5d, Flash @ %4dHz, avg = %7.3fV, dips = %3d, "
           "Smpl ms[%6.2f, %6.2f] avg %6.2f/%3d\n",
           size, pwm_freq, smoothed_avg, dips,
           stats->minPeriodInMs, stats->maxPeriodInMs,
           stats->avgPeriodInMs, stats->numSamples);
    

    if (size <= 0) {
        printf("No samples.\n");
    } 
    // Line 2: Print up to 10 evenly spaced sample values from the previous second.
    else {
        // Print everything if there are less than 10 samples.
        if (size < 10) {
            for (int i = 0; i < size; i++) {
                printf("%2d:%7.3f  ", i + 1, history[i]);
            }
        } 
        // Print everything 10th sample
        else {
            for (int j = 0; j < 10; j++) {

                // Get every 10th element.
                int index = (j * (size - 1)) / 9;
                printf("%2d:%7.3f  ", index + 1, history[index]);
            }
        }
        printf("\n");
    }
    
    free(history);
}

static void initialize(void) 
{
    Period_init();
    Sampler_init();
    Pwm_init();
    
    RotaryStateMachine_init();
    RotaryStateMachine_registerClockwiseCallback(on_clockwise_turned);
    RotaryStateMachine_registerCounterClockwiseCallback(on_counterclockwise_turned);

    pthread_mutex_init(&lcd_lock_thread, NULL);
    Lcd_init();
    UDP_init();
}

static void cleanup(void)
{
    UDP_cleanup();

    // Wait for the LCD thread to finish before cleanup.
    stop_main_thread = true;
    stop_lcd_thread = true;
    
    // pthread_cancel(lcd_thread);
    pthread_join(lcd_thread, NULL);
    pthread_mutex_destroy(&lcd_lock_thread);

    Lcd_cleanup();
    RotaryStateMachine_cleanup();
    Pwm_cleanup();
    Sampler_cleanup();
    Period_cleanup();

}

void sigintHandler(int signum)
{
    (void)signum;
    printf("\nCTRL+C detected. Cleaning up...\n");
    cleanup();
    printf("Cleanup done. Exiting.\n");
    exit(EXIT_SUCCESS);
}

/* 
 * LCD update thread.
 * This function continuously formats and sends new messages to the LCD.
 * It uses the stats pointer passed in from main.
 */
void* lcd_thread_func(void* arg) 
{
    Period_statistics_t* stats = (Period_statistics_t*) arg;
    while (!stop_lcd_thread) {
        char line1[32], line2[32], line3[32], line4[32];
        int dips = Sampler_getDips();
        snprintf(line1, sizeof(line1), "Aki W.");  
        snprintf(line2, sizeof(line2), "Flashes @%dHz", Pwm_get_frequency());
        snprintf(line3, sizeof(line3), "Dips: %d", dips);

        double max_ms = 0.0;
        pthread_mutex_lock(&lcd_lock_thread);
        max_ms = stats->maxPeriodInMs;
        pthread_mutex_unlock(&lcd_lock_thread);
        snprintf(line4, sizeof(line4), "Max ms: %.2f", max_ms);
        
        char* lcd_messages[4] = {line1, line2, line3, line4};
        Lcd_updateScreenMultiple(lcd_messages, 4);
        
        sleep(1);  // Update every second.
    }
    return NULL;
}

int main() 
{
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Failed to register SIGINT handler");
        exit(EXIT_FAILURE);
    }
    
    initialize();
    
    // Declare a statistics structure that will be shared.
    Period_statistics_t stats = {0};

    if (pthread_create(&lcd_thread, NULL, lcd_thread_func, &stats) != 0) {
        perror("Failed to create LCD thread");
        exit(EXIT_FAILURE);
    }

    // Main loop for sampling and printing light status.
    while (!stop_main_thread) {
        Period_markEvent(PERIOD_EVENT_SAMPLE_LIGHT);
        Sampler_moveCurrentDataToHistory();

        sleep(1);
        
        Period_markEvent(PERIOD_EVENT_SAMPLE_LIGHT);
        Period_getStatisticsAndClear(PERIOD_EVENT_SAMPLE_LIGHT, &stats);
        print_light_status(&stats);
    }

    // Wait for the LCD thread to finish before cleanup.
    stop_lcd_thread = true;
    pthread_cancel(lcd_thread);
    pthread_join(lcd_thread, NULL);

    cleanup();
    return 0;
}