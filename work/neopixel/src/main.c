// // NeoPixel Driver Sample
// //
// // Based off the Zephyr blinky sample application.
// // - Designed to be compiled for BeagleY-AI's MCU R5
// //   (because the custom hardware uses pins that are mapped to the MCU domain)

// #include <stdio.h>
// #include <stdlib.h>
// #include <zephyr/kernel.h>
// #include <zephyr/drivers/gpio.h>
// #include <string.h>

// #define NEO_NUM_LEDS          8   // # LEDs in our string

// // NeoPixel Timing
// // NEO_<one/zero>_<on/off>_NS
// // (These times are what the hardware needs; the delays below are hand-tuned to give these).
// #define NEO_ONE_ON_NS       700   // Stay on 700ns
// #define NEO_ONE_OFF_NS      600   // (was 800)
// #define NEO_ZERO_ON_NS      350
// #define NEO_ZERO_OFF_NS     800   // (Was 600)
// #define NEO_RESET_NS      60000   // Must be at least 50us, use 60us

// // Delay time includes 1 GPIO set action.
// volatile int junk_delay = 0;
// #define DELAY_350_NS() {}
// #define DELAY_600_NS() {for (junk_delay=0; junk_delay<9 ;junk_delay++);}
// #define DELAY_700_NS() {for (junk_delay=0; junk_delay<16 ;junk_delay++);}
// #define DELAY_800_NS() {for (junk_delay=0; junk_delay<23 ;junk_delay++);}

// #define DELAY_NS(ns) do {int target = k_cycle_get_32() + k_ns_to_cyc_near32(ns); \
// 	while(k_cycle_get_32() < target) ; } while(false)

// #define NEO_DELAY_ONE_ON()     DELAY_700_NS()
// #define NEO_DELAY_ONE_OFF()    DELAY_600_NS()
// #define NEO_DELAY_ZERO_ON()    DELAY_350_NS()
// #define NEO_DELAY_ZERO_OFF()   DELAY_800_NS()
// #define NEO_DELAY_RESET()      {DELAY_NS(NEO_RESET_NS);}

// // Device tree nodes for pin aliases
// #define LED0_NODE DT_ALIAS(led0)
// #define BTN0_NODE DT_ALIAS(btn0)
// #define NEOPIXEL_NODE DT_ALIAS(neopixel)

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
// static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BTN0_NODE, gpios);
// static const struct gpio_dt_spec neopixel = GPIO_DT_SPEC_GET(NEOPIXEL_NODE, gpios);

// static void initialize_gpio(const struct gpio_dt_spec *pPin, int direction) 
// {
// 	if (!gpio_is_ready_dt(pPin)) {
// 		printf("ERROR: GPIO pin not ready read; direction %d\n", direction);
// 		exit(EXIT_FAILURE);
// 	}

// 	int ret = gpio_pin_configure_dt(pPin, direction);
// 	if (ret < 0) {
// 		printf("ERROR: GPIO Pin Configure issue; direction %d\n", direction);
// 		exit(EXIT_FAILURE);
// 	}
// }

// int main(void)
// {
// 	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

// 	initialize_gpio(&led, GPIO_OUTPUT_ACTIVE);
// 	initialize_gpio(&btn, GPIO_INPUT);
// 	initialize_gpio(&neopixel, GPIO_OUTPUT_ACTIVE);


// 	// COLOURS
//     // - 1st element in array is 1st (bottom) on LED strip; last element is last on strip (top)
//     // - Bits: {Green/8 bits} {Red/8 bits} {Blue/8 bits} {White/8 bits}
//     uint32_t color[NEO_NUM_LEDS] = {
//         0x0f000000, // Green
//         0x000f0000, // Red
//         0x00000f00, // Blue
//         0x0000000f, // White
//         0x0f0f0f00, // White (via RGB)
//         0x0f0f0000, // Yellow
//         0x000f0f00, // Purple
//         0x0f000f00, // Teal

//         // Try these; they are birght! 
//         // (You'll need to comment out some of the above)
//         // 0xff000000, // Green Bright
//         // 0x00ff0000, // Red Bright
//         // 0x0000ff00, // Blue Bright
//         // 0xffffff00, // White
//         // 0xff0000ff, // Green Bright w/ Bright White
//         // 0x00ff00ff, // Red Bright w/ Bright White
//         // 0x0000ffff, // Blue Bright w/ Bright White
//         // 0xffffffff, // White w/ Bright White
//     };    


// 	while (true) {
// 		gpio_pin_set_dt(&neopixel, 0);
// 		DELAY_NS(NEO_RESET_NS);

// 		for(int j = 0; j < NEO_NUM_LEDS; j++) {
// 			for(int i = 31; i >= 0; i--) {
// 				if(color[j] & ((uint32_t)0x1 << i)) {
// 					gpio_pin_set_dt(&neopixel, 1);
// 					NEO_DELAY_ONE_ON();
// 					gpio_pin_set_dt(&neopixel, 0);
// 					NEO_DELAY_ONE_OFF();
// 				} else {
// 					gpio_pin_set_dt(&neopixel, 1);
// 					NEO_DELAY_ZERO_ON();
// 					gpio_pin_set_dt(&neopixel, 0);
// 					NEO_DELAY_ZERO_OFF();
// 				}
// 			}
// 		}

// 		gpio_pin_set_dt(&neopixel, 0);
// 		NEO_DELAY_RESET();

// 		// Keep looping in case we plug in NeoPixel later
// 		k_busy_wait(1 * 10000);
// 	}
// 	return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <string.h>
#include <math.h>

#include "sharedDataLayout.h"

// Memory
// ----------------------------------------
#define SHARED_MEM_BTCM_START 0x00000000  // TRM p848
#define SHARED_MEM_ATCM_START 0x00041010  // TRM p849
static void *pSharedMem = (void *) SHARED_MEM_BTCM_START;

// -----------------------------------------------------------------------------
// Existing definitions from your starter code
// -----------------------------------------------------------------------------
#define NEO_NUM_LEDS          8   // # LEDs in our string
#define NEO_ONE_ON_NS       700
#define NEO_ONE_OFF_NS      600
#define NEO_ZERO_ON_NS      350
#define NEO_ZERO_OFF_NS     800
#define NEO_RESET_NS      60000

volatile int junk_delay = 0;
#define DELAY_350_NS() {}
#define DELAY_600_NS() {for (junk_delay=0; junk_delay<9 ;junk_delay++);}
#define DELAY_700_NS() {for (junk_delay=0; junk_delay<16 ;junk_delay++);}
#define DELAY_800_NS() {for (junk_delay=0; junk_delay<23 ;junk_delay++);}

#define DELAY_NS(ns) do { int target = k_cycle_get_32() + k_ns_to_cyc_near32(ns); \
                          while(k_cycle_get_32() < target) ; \
                        } while(false)

#define NEO_DELAY_ONE_ON()     DELAY_700_NS()
#define NEO_DELAY_ONE_OFF()    DELAY_600_NS()
#define NEO_DELAY_ZERO_ON()    DELAY_350_NS()
#define NEO_DELAY_ZERO_OFF()   DELAY_800_NS()
#define NEO_DELAY_RESET()      {DELAY_NS(NEO_RESET_NS);}

#define LED0_NODE DT_ALIAS(led0)
#define BTN0_NODE DT_ALIAS(btn0)
#define NEOPIXEL_NODE DT_ALIAS(neopixel)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BTN0_NODE, gpios);
static const struct gpio_dt_spec neopixel = GPIO_DT_SPEC_GET(NEOPIXEL_NODE, gpios);

static void initialize_gpio(const struct gpio_dt_spec *pPin, int direction)
{
    if (!gpio_is_ready_dt(pPin)) {
        printf("ERROR: GPIO pin not ready; direction %d\n", direction);
        exit(EXIT_FAILURE);
    }

    int ret = gpio_pin_configure_dt(pPin, direction);
    if (ret < 0) {
        printf("ERROR: GPIO Pin Configure issue; direction %d\n", direction);
        exit(EXIT_FAILURE);
    }
}

// -----------------------------------------------------------------------------
// Utility to build the 32-bit GRBW color
// -----------------------------------------------------------------------------
static inline uint32_t make_color(uint8_t g, uint8_t r, uint8_t b, uint8_t w)
{
    // NeoPixel bit order in this code: [G(8) | R(8) | B(8) | W(8)]
    // Example: make_color(0x0f, 0x00, 0x00, 0x00) => 50%-brightness Green
    return ((uint32_t)g << 24) |
           ((uint32_t)r << 16) |
           ((uint32_t)b <<  8) |
           (uint32_t)w;
}

// -----------------------------------------------------------------------------
// Placeholder: get accelerometer X/Y tilt from somewhere
//   In reality, you might read from shared memory or from the sensor directly
// -----------------------------------------------------------------------------
static void get_accel_xy(float *x, float *y)
{
    // Example only: pretend we read from an accelerometer driver
    // Replace with real code or shared-memory read
    static float angle = 0.0f;
    angle += 0.05f;
    // Just a sine wave to illustrate changing tilt
    *x = 0.7f * sinf(angle);
    *y = 0.7f * cosf(angle);
}

// -----------------------------------------------------------------------------
// Placeholder: pick random point in [-0.5, +0.5]
// -----------------------------------------------------------------------------
static void pick_random_point(float *x_tgt, float *y_tgt)
{
    // For a real system, seed your RNG properly or use another method
    float r1 = ((float)rand()/(float)(RAND_MAX)); // in [0,1]
    float r2 = ((float)rand()/(float)(RAND_MAX));
    // Map them into [-0.5, +0.5]
    *x_tgt = (r1 - 0.5f);
    *y_tgt = (r2 - 0.5f);
}

// -----------------------------------------------------------------------------
// Fill in color[] based on tilt vs. target
// -----------------------------------------------------------------------------
static void set_led_pattern(float x_meas, float y_meas,
                            float x_tgt,  float y_tgt,
                            uint32_t color_out[NEO_NUM_LEDS])
{
    // 1) Compute error
    float dx = x_tgt - x_meas;  // if negative => we must tilt left
    float dy = y_tgt - y_meas;  // if negative => we must tilt "up" or "down", depending on orientation

    // 2) Decide color based on dx
    //    We'll define "normal" and "bright" variants of Red, Green, Blue
    uint32_t c_norm, c_bright;
    const float threshold = 0.1f;

    if      (dx < -threshold) {
        // Need to tilt more left => Red
        c_norm   = make_color(0x08, 0x00, 0x00, 0x00); // moderately-bright red
        c_bright = make_color(0xff, 0x00, 0x00, 0x00); // bright red
    }
    else if (dx > threshold) {
        // Need to tilt more right => Green
        c_norm   = make_color(0x00, 0x08, 0x00, 0x00); // moderately-bright green
        c_bright = make_color(0x00, 0xff, 0x00, 0x00); // bright green
    }
    else {
        // Centered left-right => Blue
        c_norm   = make_color(0x00, 0x00, 0x08, 0x00); // moderately-bright blue
        c_bright = make_color(0x00, 0x00, 0xff, 0x00); // bright blue
    }

    // 3) Decide vertical pattern based on dy
    //    - If below target => show 3 in top half
    //    - If above target => show 3 in bottom half
    //    - If on target => all on
    //    We'll treat index 0 as bottom, 7 as top.
    //    "Top half" = indices 5,6,7
    //    "Bottom half" = indices 0,1,2
    //    Middle LED of the 3 is bright.

    // Clear the array first
    for (int i = 0; i < NEO_NUM_LEDS; i++) {
        color_out[i] = 0x00000000; // off
    }

    if (dy < -threshold) {
        // Board is below the target => we want user to tilt up more
        // => Light top half (5,6,7)
        color_out[5] = c_norm;
        color_out[6] = c_bright; // center is bright
        color_out[7] = c_norm;
    }
    else if (dy > threshold) {
        // Board is above the target => we want user to tilt down
        // => Light bottom half (0,1,2)
        color_out[0] = c_norm;
        color_out[1] = c_bright; // center is bright
        color_out[2] = c_norm;
    }
    else {
        // On target vertically => all on with c_norm, or you could make them all bright
        for (int i = 0; i < NEO_NUM_LEDS; i++) {
            color_out[i] = c_norm;
        }
    }
}

// -----------------------------------------------------------------------------
// Send color[] out to the NeoPixel strip (same as your starter code's loop body)
// -----------------------------------------------------------------------------
static void neopixel_send(uint32_t color_out[NEO_NUM_LEDS])
{
    // Send the reset pulse first
    gpio_pin_set_dt(&neopixel, 0);
    DELAY_NS(NEO_RESET_NS);

    // For each LED, shift out 32 bits (GRBW)
    for(int j = 0; j < NEO_NUM_LEDS; j++) {
        uint32_t c = color_out[j];
        for(int i = 31; i >= 0; i--) {
            if(c & ((uint32_t)1 << i)) {
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

// -----------------------------------------------------------------------------
// main()
// -----------------------------------------------------------------------------
int main(void)
{
    printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

    // Init the GPIO pins
    initialize_gpio(&led, GPIO_OUTPUT_ACTIVE);
    initialize_gpio(&btn, GPIO_INPUT);
    initialize_gpio(&neopixel, GPIO_OUTPUT_ACTIVE);

    // Our 8-LED color buffer
    static uint32_t color[NEO_NUM_LEDS];

    // Randomly pick a target point
    float x_target, y_target;
    pick_random_point(&x_target, &y_target);

    printf("Random target picked: (%.3f, %.3f)\n", x_target, y_target);

    while (true) {
        // 1) Get the current tilt (placeholder)
        float x_meas, y_meas;
        get_accel_xy(&x_meas, &y_meas);

        // 2) Fill the color array based on the tilt vs. target
        set_led_pattern(x_meas, y_meas, x_target, y_target, color);

        // 3) Send color array out to the NeoPixel
        neopixel_send(color);

        // 4) Wait ~100ms => ~10 Hz
        // k_msleep(100);
        // k_msleep(100);

        // Update memory
        MEM_FLOAT(X_MEASURE_OFFSET) = x_meas;
        MEM_FLOAT(Y_MEASURE_OFFSET) = y_meas;
		
        // 1s
        k_busy_wait(250 * 1000);	

        // Optionally: you could detect "success" if within +/-0.1 in both axes,
        // and then pick a new random point or do something else, e.g.:
        /*
        float dx = fabsf(x_target - x_meas);
        float dy = fabsf(y_target - y_meas);
        if (dx < 0.1f && dy < 0.1f) {
            // user is "on target"
            pick_random_point(&x_target, &y_target);
            printf("New random target: (%.3f, %.3f)\n", x_target, y_target);
        }
        */
    }

    return 0;
}
