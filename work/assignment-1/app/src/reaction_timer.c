#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "hal/led.h"
#include "hal/joystick.h"

#include <limits.h>

static long long getTimeInMs(void) {
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

static void sleepForMs(long long delayInMs) {
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;

    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;

    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

void random_delay() {
    // Random time between 500ms and 3000ms
    long long random_time_ms = (rand() % 2501) + 500;
    sleepForMs(random_time_ms);
}

int main ()
{
    printf("Hello embedded world, from Aki!\n");

    Joystick *joystick = Joystick_init();

    if (joystick == NULL) {
        perror("main: Failed to initialize a joystick\n");
        exit(EXIT_FAILURE);
    }

    Led *led_green = Led_init(Led_Green);
    if (led_green == NULL) {
        perror("main: Failed to initialize a green LED\n");
        exit(EXIT_FAILURE);
    }

    Led *led_red = Led_init(Led_Red);
    if (led_red == NULL) {
        perror("main: Failed to initialize a red LED\n");
        exit(EXIT_FAILURE);
    }

    bool game_over = false;
    long long best_reaction_time = LLONG_MAX;
    while (!game_over) {
        // 1.) Flash LEDs to get ready.
        printf("Get ready...\n");
        for (int i = 0; i < 4; i++) {
            Led_flash(led_green);
            Led_flash(led_red);
        }

        bool is_joystick_up = Joystick_is_up(joystick);
        bool is_joystick_down = Joystick_is_down(joystick);

        // 2.) Tell the user to not touch the joystick
        while (is_joystick_up || is_joystick_down) {
            printf("Please let go of joystick.\n");

            is_joystick_up = Joystick_is_up(joystick);
            is_joystick_down = Joystick_is_down(joystick);
            sleep(1);
        }

        // 3.) Wait a random time between 0.5s and 3s
        random_delay();

        is_joystick_up = Joystick_is_up(joystick);
        is_joystick_down = Joystick_is_down(joystick);
        // 4.) If the user tries to push the joystick before timer started.
        if (is_joystick_up || is_joystick_down) {
            printf("Too soon!\n");
            continue;
        }

        // 5.) Pick a random direction, up is either 1 or 0.
        bool direction_up = rand() % 2;
        if (direction_up) {
            printf("Press UP now!\n");
            Led_turn_on(led_green);
        } else {
            printf("Press DOWN now!\n");
            Led_turn_on(led_red);
        }

        // 6.) Start the reaction timer.
        long long start_time = getTimeInMs();

        // Wait for joystick input.
        is_joystick_up = Joystick_is_up(joystick);
        is_joystick_down = Joystick_is_down(joystick);
        bool is_joystick_left = Joystick_is_left(joystick);
        bool is_joystick_right = Joystick_is_right(joystick);

        while (!is_joystick_up && !is_joystick_down && !is_joystick_left && !is_joystick_right) {
            long long time_diff = getTimeInMs() - start_time;

            is_joystick_up = Joystick_is_up(joystick);
            is_joystick_down = Joystick_is_down(joystick);
            is_joystick_left = Joystick_is_left(joystick);
            is_joystick_right = Joystick_is_right(joystick);

            if (time_diff > 5000) {
                printf("Time out! Game over!\n");
                game_over = true;
                break;
            }
        }

        // Break out of the loop if the game is over.
        if (game_over) {
            break;
        }

        // Invalid input: Left or right joystick
        if (is_joystick_left || is_joystick_right) {
            printf("No LEFT or RIGHT joystick allowed! Game over!\n");
            break;
        }

        // 7.) Calculate and keep track of the best reaction time.
        // Check if the random direction is up/down and user correctly presses up/down.
        long long reaction_time = getTimeInMs() - start_time;
        if ((direction_up && is_joystick_up) || (!direction_up && is_joystick_down)) {
            printf("Good job!\n");

            if (reaction_time < best_reaction_time) {
                best_reaction_time = reaction_time;
                printf("Record breaking! New best reaction time is %lld ms\n", best_reaction_time);
            }

            printf("Your reaction time is %lld ms\n", reaction_time);
        }
        // Wrong direction.
        else {
            printf("Oops, wrong direction, try again.\n");

            // Turn off existing LED.
            Led_turn_off(led_red);
            Led_turn_off(led_green);

            Led_flash(led_red);
            usleep(200000);

            Led_flash(led_red);
            usleep(200000);

            Led_flash(led_red);
            usleep(200000);

            Led_flash(led_red);
            usleep(200000);

            Led_flash(led_red);
            usleep(200000);
        }

        printf("The game will restart in 5s...\n");
        sleep(5);
    }

    Led_turn_off(led_green);
    Led_turn_off(led_red);

    Led_cleanup(led_green);
    Led_cleanup(led_red);
    Joystick_cleanup(joystick);

    return 0;
}