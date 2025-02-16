// Reference: Lecture slide
#include "hal/rotary_statemachine.h"
#include "hal/gpio.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>


#include <pthread.h>

// Pin config info: GPIO 24 (Rotary Encoder PUSH)
//   $ gpiofind GPIO24
//   >> gpiochip0 10

// Pin configuration
// Line A
// gpiofind GPIO16
// >> gpiochip2 7
// Line B
// gpiofind GPIO17
// >> gpiochip2 8
#define GPIO_LINE_A_CHIP                    GPIO_CHIP_2
#define GPIO_LINE_A_NUMBER                  7

#define GPIO_LINE_B_CHIP                    GPIO_CHIP_2
#define GPIO_LINE_B_NUMBER                  8

static bool isInitialized = false;

struct GpioLine* line_A = NULL;
struct GpioLine* line_B = NULL;

static atomic_int counter = 0;

/*
    Define the Statemachine Data Structures
*/
struct stateEvent {
    struct state* pNextState;
    void (*action)();
};

struct state {
    struct stateEvent A_rising;
    struct stateEvent A_falling;
    struct stateEvent B_rising;
    struct stateEvent B_falling;
};

static pthread_t event_thread;
static pthread_mutex_t lock_thread;
static bool stop_thread = false;

/*
    START STATEMACHINE
*/
static void on_clockwise(void)
{
    counter++;
    printf("Clockwise step detected. New counter: %d\n", counter);
}

static void on_counter_clockwise(void)
{
    counter--;
    printf("Counterclockwise step detected. New counter: %d\n", counter);
}

struct state states[] = {
    // When at state: Rest
    // A rises -> Stay at same state.
    // A falls -> Go to State 1.
    // B rises -> Stay at same state.
    // B falls -> Go to State 3.
    { 
        .A_rising = {&states[0], NULL},
        .A_falling = {&states[1], on_clockwise},
        .B_rising = {&states[0], NULL},
        .B_falling = {&states[3], on_counter_clockwise},
    },

    // When at state: State 1
    // A rises -> Go to Rest.
    // A falls -> Stay at same state.
    // B rises -> Stay at same state.
    // B falls -> Go to State 2.
    { 
        .A_rising = {&states[0], on_counter_clockwise},
        .A_falling = {&states[1], NULL},
        .B_rising = {&states[1], NULL},
        .B_falling = {&states[2], on_clockwise},
    },

    // When at state: State 2
    // A rises -> Go to State 3.
    // A falls -> Stay at same state.
    // B rises -> Go to State 1.
    // B falls -> Stay at same state.
    { 
        .A_rising = {&states[3], on_clockwise},
        .A_falling = {&states[2], NULL},
        .B_rising = {&states[1], on_counter_clockwise},
        .B_falling = {&states[2], NULL},
    },

    // When at state: State 3
    // A rises -> Stay at same state.
    // A falls -> Go to State 2.
    // B rises -> Go to Rest.
    // B falls -> Stay at same state.
    { 
        .A_rising = {&states[3], NULL},
        .A_falling = {&states[2], on_counter_clockwise},
        .B_rising = {&states[0], on_clockwise},
        .B_falling = {&states[3], NULL},
    },
};
/*
    END STATEMACHINE
*/

struct state* pCurrentState = &states[0];

int RotaryStateMachine_getValue()
{
    return counter;
}

static void* listen_for_events(void *arg)
{
    (void)arg; // This is not being used, without this, getting unused parameter.
    while (!stop_thread) {
        struct gpiod_line_bulk bulkEvents;
        int numEvents = Gpio_waitForLineChange(line_A, line_B, &bulkEvents);
        
        // Iterate over the event
        for (int i = 0; i < numEvents; i++) {
            // Get the line handle for this event
            struct gpiod_line *line_handle = gpiod_line_bulk_get_line(&bulkEvents, i);

            // Get the number of this line
            unsigned int this_line_number = gpiod_line_offset(line_handle);

            // Get the line event
            struct gpiod_line_event event;
            if (gpiod_line_event_read(line_handle, &event) == -1) {
                perror("Line Event");
                exit(EXIT_FAILURE);
            }

            // Run the state machine
            bool isRising = event.event_type == GPIOD_LINE_EVENT_RISING_EDGE;
            bool isFalling = event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE;

            // Pick the proper event based on the line number
            struct stateEvent* pStateEvent = NULL;
            if (this_line_number == GPIO_LINE_A_NUMBER) {
                pthread_mutex_lock(&lock_thread); 
                {
                    if (isRising) {
                        pStateEvent = &pCurrentState->A_rising;
                    } else if (isFalling) {
                        pStateEvent = &pCurrentState->A_falling;
                    }
                }
                pthread_mutex_unlock(&lock_thread);
            } else if (this_line_number == GPIO_LINE_B_NUMBER) {
                pthread_mutex_lock(&lock_thread);
                {
                    if (isRising) {
                        pStateEvent = &pCurrentState->B_rising;
                    } else if (isFalling) {
                        pStateEvent = &pCurrentState->B_falling;
                    }
                }
                pthread_mutex_unlock(&lock_thread);
            } else {
                perror("RotaryStateMachine_listen: Unexpected GPIO line number.");
                exit(EXIT_FAILURE);
            }

            // Do the action
            if (pStateEvent->action != NULL) {
                pStateEvent->action();
            }

            pthread_mutex_lock(&lock_thread);
            {
                pCurrentState = pStateEvent->pNextState;
            }
            pthread_mutex_unlock(&lock_thread);
            
            // DEBUG INFO ABOUT STATEMACHINE
            // #if true
            // int newState = (pCurrentState - &states[0]);
            // double time = event.ts.tv_sec + event.ts.tv_nsec / 1000000000.0;
            // printf("State machine Debug: i=%d/%d  line num/dir = %d %8s -> new state %d     [%f]\n", 
            //     i, 
            //     numEvents,
            //     this_line_number, 
            //     isRising ? "RISING": "falling", 
            //     newState,
            //     time);
            // #endif
        }
    }

    return NULL;
}

void RotaryStateMachine_init()
{
    assert(!isInitialized);
    line_A = Gpio_openForEvents(GPIO_LINE_A_CHIP, GPIO_LINE_A_NUMBER);
    line_B = Gpio_openForEvents(GPIO_LINE_B_CHIP, GPIO_LINE_B_NUMBER);

    stop_thread = false;
    pthread_mutex_init(&lock_thread, NULL);

    if (pthread_create(&event_thread, NULL, listen_for_events, NULL) != 0) {
        perror("RotaryStateMachine_init: Failed to create the event thread.");
        exit(EXIT_FAILURE);
    }

    isInitialized = true;
}

void RotaryStateMachine_cleanup()
{
    assert(isInitialized);
    isInitialized = false;
    
    stop_thread = true;
    pthread_join(event_thread, NULL);
    pthread_mutex_destroy(&lock_thread);

    Gpio_close(line_A);
    Gpio_close(line_B);
}

// // TODO: This should be on a background thread!
// void RotaryStateMachine_doState()
// {
//     assert(isInitialized);

//     printf("\n\nWaiting for an event...\n");
//     while (true) {
//         struct gpiod_line_bulk bulkEvents;
//         int numEvents = Gpio_waitForLineChange(line_A, line_B, &bulkEvents);
        
//         // Iterate over the event
//         for (int i = 0; i < numEvents; i++) {
//             // Get the line handle for this event
//             struct gpiod_line *line_handle = gpiod_line_bulk_get_line(&bulkEvents, i);

//             // Get the number of this line
//             unsigned int this_line_number = gpiod_line_offset(line_handle);

//             // Get the line event
//             struct gpiod_line_event event;
//             if (gpiod_line_event_read(line_handle,&event) == -1) {
//                 perror("Line Event");
//                 exit(EXIT_FAILURE);
//             }

//             // Run the state machine
//             bool isRising = event.event_type == GPIOD_LINE_EVENT_RISING_EDGE;
//             bool isFalling = event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE;

//             // Pick the proper event based on the line number
//             struct stateEvent* pStateEvent = NULL;
//             if (this_line_number == GPIO_LINE_A_NUMBER) {
//                 if (isRising) {
//                     pStateEvent = &pCurrentState->A_rising;
//                 } else if (isFalling) {
//                     pStateEvent = &pCurrentState->A_falling;
//                 }
//             } else if (this_line_number == GPIO_LINE_B_NUMBER) {
//                 if (isRising) {
//                     pStateEvent = &pCurrentState->B_rising;
//                 } else if (isFalling) {
//                     pStateEvent = &pCurrentState->B_falling;
//                 }
//             } else {
//                 fprintf(stderr, "Unexpected GPIO line number: %u\n", this_line_number);
//                 continue;
//             }

//             // Do the action
//             if (pStateEvent->action != NULL) {
//                 pStateEvent->action();
//             }
//             pCurrentState = pStateEvent->pNextState;

//             // DEBUG INFO ABOUT STATEMACHINE
//             // #if true
//             // int newState = (pCurrentState - &states[0]);
//             // double time = event.ts.tv_sec + event.ts.tv_nsec / 1000000000.0;
//             // printf("State machine Debug: i=%d/%d  line num/dir = %d %8s -> new state %d     [%f]\n", 
//             //     i, 
//             //     numEvents,
//             //     this_line_number, 
//             //     isRising ? "RISING": "falling", 
//             //     newState,
//             //     time);
//             // #endif
//         }
//     }
// }
