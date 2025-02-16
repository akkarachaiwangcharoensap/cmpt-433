#include "hal/led.h"
#include <assert.h>
#include <unistd.h>

#define LED_RED_BRIGHTNESS_FILE "/sys/class/leds/PWR/brightness"
#define LED_GREEN_BRIGHTNESS_FILE "/sys/class/leds/ACT/brightness"

struct Led {
    Led_Color color;
    const char *file_name;
    bool is_initialized;
};

// Initialize an LED given its supported LED color.
Led* Led_init(Led_Color color) 
{
    printf("LED - Initializing\n");

    // Heap allocation
    Led *led = (Led*)malloc(sizeof(Led));
    led->is_initialized = true;

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
    
    led->is_initialized = true;
    srand(time(0));

    return led;
}

// An internal function that sets LED brightness to 1 or 0.
static void set_led_state(Led *led, int state)
{
    // Ensure led is available before any operation.
    assert(led != NULL);
    assert(led->is_initialized);

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

void Led_turn_on(Led *led)
{
    set_led_state(led, 1);
}

void Led_turn_off(Led *led)
{
    set_led_state(led, 0);
}

bool Led_is_on(Led *led)
{
    // Ensure led is available before any operation.
    assert(led != NULL);
    assert(led->is_initialized);

    FILE *file = fopen(led->file_name, "r");
    if (file == NULL) {
        perror("led_is_on: Error opening LED file for reading.");
        return false;
    }

    int state = fgetc(file);
    fclose(file);

    return state == '1';
}

bool Led_is_off(Led *led)
{
    return !Led_is_on(led);
}

void Led_flash(Led *led)
{
    // Ensure led is available before any operation.
    assert(led != NULL);

    Led_turn_on(led);
    usleep(250000);
    Led_turn_off(led);
    usleep(250000);
}

void Led_cleanup(Led *led)
{
    // Free any memory, close files, ...
    printf("LED - Cleanup\n");

    assert(led->is_initialized);
    led->is_initialized = false;

    // Ensure led is available before any operation.
    assert(led != NULL);
    free(led);
}
