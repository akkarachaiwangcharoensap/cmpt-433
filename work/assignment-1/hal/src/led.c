#include "hal/led.h"
#include <assert.h>

#define LED_RED_BRIGHTNESS_FILE "/sys/class/leds/PWR/brightness"
#define LED_GREEN_BRIGHTNESS_FILE "/sys/class/leds/ACT/brightness"

struct Led {
    Led_Color color;
    const char *file_name;
};

// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

// Initialize an LED given its supported LED color.
Led* led_init(Led_Color color) 
{
    printf("LED - Initializing\n");
    assert(!is_initialized);

    // Heap allocation
    Led *led = (Led*)malloc(sizeof(Led));

    if (led == NULL) {
        perror("led_init: Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }

    led->file_name = NULL;
    led->color = color;

    switch (color) {
        case Led_Green:
            printf("LED - Green\n");
            led->file_name = LED_GREEN_BRIGHTNESS_FILE;
            break;
        case Led_Red:
            printf("LED - Red\n");
            led->file_name = LED_RED_BRIGHTNESS_FILE;
            break;
        default:
            perror("led_init: Error LED color not supported.");
            free(led);
            return NULL;
    }
    
    is_initialized = true;
    srand(time(0));

    return led;
}

// An internal function that sets LED brightness to 1 or 0.
static void set_led_state(Led *led, int state)
{
    assert(is_initialized);

    // Ensure led is available before any operation.
    assert(led != NULL);

    // Ensure 1 or 0, on or off.
    if (state != 1 && state != 0) {
        perror("Unexpected parameter's value.");
        return;
    }

    FILE *file = fopen(led->file_name, "w");
    if (file == NULL) {
        perror("set_led_state: Error opening LED file.");
        exit(EXIT_FAILURE);
    }

    // Write to file
    fprintf(file, "%d", state);

    // Cleanup
    fclose(file);
}

void led_turn_on(Led *led)
{
    set_led_state(led, 1);
}

void led_turn_off(Led *led)
{
    set_led_state(led, 0);
}

bool led_is_on(Led *led)
{
    assert(is_initialized);

    // Ensure led is available before any operation.
    assert(led != NULL);

    FILE *file = fopen(led->file_name, "r");
    if (file == NULL) {
        perror("led_is_on: Error opening LED file for reading.");
        return false;
    }

    int state = fgetc(file);
    fclose(file);

    return state == '1';
}

bool led_is_off(Led *led)
{
    return !led_is_on(led);
}

void led_cleanup(Led *led)
{
    // Free any memory, close files, ...
    printf("LED - Cleanup\n");

    assert(is_initialized);

    // Ensure led is available before any operation.
    assert(led != NULL);
    free(led);

    is_initialized = false;
}