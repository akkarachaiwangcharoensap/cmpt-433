#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "hal/led.h"
// #include "hal/light_sensor.h"

#include <limits.h>
#include <stdint.h>

#include <unistd.h>
#include "hal/gpio.h"
#include "hal/rotary_statemachine.h"
#include "hal/sampler.h"
#include "hal/pwm.h"
#include <time.h>

#include <signal.h>

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

void on_knob_turned(double normalized) {
    Pwm_set_flash_speed(normalized);
}

// On CTRL + C
void sigintHandler(int signum)
{
    (void)signum; // Avoid unused parameter warning.
    printf("\nCTRL+C detected. Cleaning up...\n");

    Sampler_cleanup();
    RotaryStateMachine_cleanup();
    Pwm_cleanup();

    printf("Cleanup done. Exiting.\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    // Register the SIGINT handler.
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Failed to register SIGINT handler");
        exit(EXIT_FAILURE);
    }

    // Sampler_init();
    // while (true) {
    //     int history_size = Sampler_getHistorySize();
    //     int total_size = Sampler_getNumSamplesTaken();

    //     printf("history size: %d\n", history_size);
    //     printf("total size: %d\n", total_size);
        
    //     sleep(1);
    //     Sampler_moveCurrentDataToHistory();

    // }
    // Sampler_cleanup();

    printf("Rotary Testing...\n");

    // Startup & Initialization
    Pwm_init();
    RotaryStateMachine_init();
    RotaryStateMachine_registerCallback(on_knob_turned);

    // TESTING State machine
    // while (true) {
        // TODO: This should be on it's own thread!
        // RotaryStateMachine_doState();

        // printf("Counter at %+5d\n", RotaryStateMachine_getValue());
        // usleep(500);
    // }

    Sampler_init();
    while (true) {
        int history_size = Sampler_getHistorySize();
        int total_size = Sampler_getNumSamplesTaken();

        printf("history size: %d\n", history_size);
        printf("total size: %d\n", total_size);
        
        sleep(1);
        Sampler_moveCurrentDataToHistory();

    }
    
    Sampler_cleanup();
    RotaryStateMachine_cleanup();
    Pwm_cleanup();

    printf("\nDone!\n");

    return 0;
}