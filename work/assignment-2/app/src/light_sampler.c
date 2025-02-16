#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "hal/led.h"
#include "hal/joystick.h"

#include <limits.h>
#include <stdint.h>



#include <unistd.h>
#include "hal/gpio.h"
#include "hal/rotary_statemachine.h"
#include <time.h>


// static long long getTimeInMs(void) {
//     struct timespec spec;
//     clock_gettime(CLOCK_REALTIME, &spec);
//     long long seconds = spec.tv_sec;
//     long long nanoSeconds = spec.tv_nsec;
//     long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
//     return milliSeconds;
// }

// static void sleepForMs(long long delayInMs) {
//     const long long NS_PER_MS = 1000 * 1000;
//     const long long NS_PER_SECOND = 1000000000;

//     long long delayNs = delayInMs * NS_PER_MS;
//     int seconds = delayNs / NS_PER_SECOND;
//     int nanoseconds = delayNs % NS_PER_SECOND;

//     struct timespec reqDelay = {seconds, nanoseconds};
//     nanosleep(&reqDelay, (struct timespec *) NULL);
// }

// void random_delay() {
//     // Random time between 500ms and 3000ms
//     long long random_time_ms = (rand() % 2501) + 500;
//     sleepForMs(random_time_ms);
// }

int main()
{
    // printf("Hello embedded world, from Aki!\n");
    // printf("Press UP if a green LED flashing, DOWN if a red LED flashing.\n (Press LEFT or RIGHT to stop the game.)\n");

    Joystick *joystick = Joystick_init();

    if (joystick == NULL) {
        perror("main: Failed to initialize a joystick\n");
        exit(EXIT_FAILURE);
    }

    printf("Reading light value...");
    uint16_t light_value = Joystick_read_light(joystick);
    while (true) {
        printf("Light value: %d\n", light_value);
        light_value = Joystick_read_light(joystick);
        sleep(1);
    }
    
    Joystick_cleanup(joystick);

    // printf("Rotary Testing...\n");

    // // Startup & Initialization
    // Gpio_initialize();
    // RotaryStateMachine_init();

    // // TESTING State machine
    // while (true) {
    //     // TODO: This should be on it's own thread!
    //     // RotaryStateMachine_doState();

    //     printf("Counter at %+5d\n", RotaryStateMachine_getValue());
    //     usleep(500);
    // }

    // RotaryStateMachine_cleanup();
    // Gpio_cleanup();

    // printf("\nDone!\n");

    return 0;
}