#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "sharedDataLayout.h"

/**
 * This code comes from the A4 example code.
 */
// -----------------------------------------------------------------------------
// Shared Memory Setup
// -----------------------------------------------------------------------------
#define SHARED_MEM_BTCM_START  0x00000000  // TRM p848
static void *pSharedMem = (void *) SHARED_MEM_BTCM_START;

// -----------------------------------------------------------------------------
// NeoPixel / GPIO Setup
// -----------------------------------------------------------------------------
#define NEO_NUM_LEDS         8
#define NEO_ONE_ON_NS      700
#define NEO_ONE_OFF_NS     600
#define NEO_ZERO_ON_NS     350
#define NEO_ZERO_OFF_NS    800
#define NEO_RESET_NS     60000

// Dummy delay macros or placeholders for busy-wait loops:
volatile int junk_delay = 0;
#define DELAY_350_NS() {}
#define DELAY_600_NS() {for (junk_delay=0; junk_delay<9 ;junk_delay++);}
#define DELAY_700_NS() {for (junk_delay=0; junk_delay<16 ;junk_delay++);}
#define DELAY_800_NS() {for (junk_delay=0; junk_delay<23 ;junk_delay++);}

#define DELAY_NS(ns) do { \
    int target = k_cycle_get_32() + k_ns_to_cyc_near32(ns); \
    while(k_cycle_get_32() < target) { /* spin */ } \
} while(false)

#define NEO_DELAY_ONE_ON()     DELAY_700_NS()
#define NEO_DELAY_ONE_OFF()    DELAY_600_NS()
#define NEO_DELAY_ZERO_ON()    DELAY_350_NS()
#define NEO_DELAY_ZERO_OFF()   DELAY_800_NS()
#define NEO_DELAY_RESET()      DELAY_NS(NEO_RESET_NS)

// Example GPIO spec (adapt to your board’s device tree)
#define LED0_NODE       DT_ALIAS(led0)
#define BTN0_NODE       DT_ALIAS(btn0)
#define NEOPIXEL_NODE   DT_ALIAS(neopixel)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BTN0_NODE, gpios);
static const struct gpio_dt_spec neopixel = GPIO_DT_SPEC_GET(NEOPIXEL_NODE, gpios);

static void initialize_gpio(const struct gpio_dt_spec *pPin, int direction)
{
    if (!gpio_is_ready_dt(pPin)) {
        printf("ERROR: GPIO pin not ready; direction %d\n", direction);
        return;
    }
    int ret = gpio_pin_configure_dt(pPin, direction);
    if (ret < 0) {
        printf("ERROR: GPIO Pin Configure issue; direction %d\n", direction);
    }
}

// -----------------------------------------------------------------------------
// Utility to build the 32-bit GRBW color
// -----------------------------------------------------------------------------
static inline uint32_t make_color(uint8_t g, uint8_t r, uint8_t b, uint8_t w)
{
    // Bits: [ G(8) | R(8) | B(8) | W(8) ]
    return ((uint32_t)g << 24) |
           ((uint32_t)r << 16) |
           ((uint32_t)b <<  8) |
           (uint32_t)w;
}

// -----------------------------------------------------------------------------
// Decide color (red/green/blue) based on how we need to tilt left/right
// Decide vertical LED pattern based on up/down
// -----------------------------------------------------------------------------
static void set_led_pattern(float x_meas, float y_meas,
                            float x_tgt,  float y_tgt,
                            uint32_t color_out[NEO_NUM_LEDS])
{
    // Error in both axes.
    // Negative => board is too low (target is above)
    // Positive => board is too high (target is below)
    float dx = x_tgt - x_meas;
    
    // Negative => tilt left, positive => tilt right
    float dy = y_tgt - y_meas;
    
    // Normal and bright colors.
    uint32_t c_norm, c_bright;
    const float threshold = 0.1f;

    bool is_center = false, on_target = false;

    // Tilt to the left: red
    if (dx < -threshold) {
        c_norm   = make_color(0x08, 0x00, 0x00, 0x00);
        c_bright = make_color(0xff, 0x00, 0x00, 0x00);
        is_center = false;
    }
    // Tilt to the right: green
    else if (dx > threshold) {
        c_norm   = make_color(0x00, 0x08, 0x00, 0x00);
        c_bright = make_color(0x00, 0xff, 0x00, 0x00);
        is_center = false;
    }
    // Center: blue
    else {
        c_norm   = make_color(0x00, 0x00, 0x08, 0x00);
        c_bright = make_color(0x00, 0x00, 0xff, 0x00);
        is_center = true;
    }

    // Turn off/reset all LEDs first before lighting up all LEDs if on target.
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        color_out[i] = 0x00000000;
    }

    // If the board is "on target" (vertically within threshold), light all LEDs.
    if (fabsf(dy) <= threshold) {
        on_target = true;
        for (int i = 0; i < NEO_NUM_LEDS; i++) {
            color_out[i] = c_norm;
        }
    }
    else {
        on_target = false;

        // Idea: ChatGPT o3-mini-high
        // Compute normalized error in the range [0,1].
        float error_norm = (fabsf(dy) - threshold) / (1.0f - threshold);
        if (error_norm >= 1.0f)
            error_norm = 1.0f;

        // Threshold above which adjacent LEDs are disabled when at the edges.
        const float disable_adjacent_threshold = 0.9f;

        // Center LED index and valid adjacent LEDs.
        int center_index;
        int lower_bound, upper_bound;

        // Board is too high (target is below)
        if (dy > threshold) {
            lower_bound = 0;
            upper_bound = 3;
            // Minimal error => center index 3; maximum error => index 0.
            center_index = 3 - (int)round(error_norm * 3.0f);
        } 
        // Board is too low (target is above)
        else {
            lower_bound = 4;
            upper_bound = 7;
            // Minimal error => center index 4; maximum error => index 7.
            center_index = 4 + (int)round(error_norm * 3.0f);
        }

        // Always light the center LED as bright.
        color_out[center_index] = c_bright;

        // If the error is extreme and the center LED is at the edge, 
        // then do not light the adjacent LEDs.
        bool disable_adjacent = false;
        if ((center_index == lower_bound || center_index == upper_bound) &&
            error_norm >= disable_adjacent_threshold)
        {
            disable_adjacent = true;
        }

        // Light the adjacent LEDs only if we are not disabling them.
        if (!disable_adjacent) {
            if ((center_index - 1) >= 0)
                color_out[center_index - 1] = c_norm;
            if ((center_index + 1) <= 7)
                color_out[center_index + 1] = c_norm;
        }
    }

    MEM_UINT8(FIRING_IN_RANGE_OFFSET) = (is_center && on_target);
}

// -----------------------------------------------------------------------------
// Send color_out[] to the NeoPixel strip
// -----------------------------------------------------------------------------
static void neopixel_send(uint32_t color_out[NEO_NUM_LEDS])
{
    // Send the reset pulse
    gpio_pin_set_dt(&neopixel, 0);
    NEO_DELAY_RESET();

    // For each LED, shift out 32 bits (GRBW)
    for (int j = 0; j < NEO_NUM_LEDS; j++) {
        uint32_t c = color_out[j];
        for (int i = 31; i >= 0; i--) {
            if (c & ((uint32_t)1 << i)) {
                // '1' bit
                gpio_pin_set_dt(&neopixel, 1);
                NEO_DELAY_ONE_ON();
                gpio_pin_set_dt(&neopixel, 0);
                NEO_DELAY_ONE_OFF();
            } else {
                // '0' bit
                gpio_pin_set_dt(&neopixel, 1);
                NEO_DELAY_ZERO_ON();
                gpio_pin_set_dt(&neopixel, 0);
                NEO_DELAY_ZERO_OFF();
            }
        }
    }

    // Latch/reset
    gpio_pin_set_dt(&neopixel, 0);
    NEO_DELAY_RESET();
}

void explosion_animation(void)
{
    uint32_t explosion[NEO_NUM_LEDS];

    // Frame 1: Bright yellow (red + green)
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        explosion[i] = make_color(0xff, 0xff, 0x00, 0x00);
    }
    neopixel_send(explosion);
    k_busy_wait(150 * 1000); // 150ms

    // Frame 2: Orange (reduce green intensity)
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        explosion[i] = make_color(0x80, 0xff, 0x00, 0x00);
    }
    neopixel_send(explosion);
    k_busy_wait(150 * 1000); // 150ms

    // Frame 3: Red
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        explosion[i] = make_color(0x00, 0xff, 0x00, 0x00);
    }
    neopixel_send(explosion);
    k_busy_wait(200 * 1000); // 200ms

    // Clear LEDs
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        explosion[i] = 0x00000000;
    }
    neopixel_send(explosion);

    MEM_UINT8(FIRING_STATUS_OFFSET) = 0;
}

void miss_animation(void)
{
    uint32_t miss[NEO_NUM_LEDS];

    // Flash yellow to indicate a miss
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        miss[i] = make_color(0xff, 0xff, 0x00, 0x00);
    }
    neopixel_send(miss);
    k_busy_wait(250 * 1000); // 250ms on

    // Turn off LEDs
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        miss[i] = 0x00000000;
    }
    neopixel_send(miss);
    k_busy_wait(250 * 1000); // 250ms off

    MEM_UINT8(FIRING_STATUS_OFFSET) = 0;
}

void turn_off_LEDs()
{
    uint32_t miss[NEO_NUM_LEDS];
    // Turn off LEDs
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        miss[i] = 0x00000000;
    }
    neopixel_send(miss);
}

int main(void)
{
    printf("R5: Tilt-to-Target App starting...\n");

    // Initialize the GPIO pins
    initialize_gpio(&led, GPIO_OUTPUT_ACTIVE);
    initialize_gpio(&btn, GPIO_INPUT);
    initialize_gpio(&neopixel, GPIO_OUTPUT_ACTIVE);

    float x_meas, y_meas, x_target, y_target;

    uint8_t firing_status;

    uint32_t color[NEO_NUM_LEDS];

    MEM_UINT8(FIRING_IN_RANGE_OFFSET) = false;
    MEM_UINT8(TERMINATE_PROGRAM_FLAG_OFFSET) = false;
    
    while (true) {
        x_meas = MEM_FLOAT(NORMALIZED_X_ROTATION_OFFSET);
        y_meas = MEM_FLOAT(NORMALIZED_Y_ROTATION_OFFSET);

        x_target = MEM_FLOAT(X_TARGET_OFFSET);
        y_target = MEM_FLOAT(Y_TARGET_OFFSET);

        firing_status = MEM_UINT8(FIRING_STATUS_OFFSET);

        // Hit animation
        if (firing_status == 1) {
            explosion_animation();
        } 
        // Miss animation
        else if (firing_status == 2) {
            miss_animation();
        } 
        // Default
        else {
            set_led_pattern(y_meas, x_meas, x_target, y_target, color);
        }
        
        neopixel_send(color);

        if (MEM_UINT8(TERMINATE_PROGRAM_FLAG_OFFSET) == true) {
            break;
        }

        // Sleep ~250 ms (4 Hz)
        k_busy_wait(250 * 1000);
    }

    turn_off_LEDs();

    return 0;
}