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

// gpiofind GPIO24
// >> gpiochip0 10
#define GPIO_BUTTON_CHIP                    GPIO_CHIP_0
#define GPIO_BUTTON_NUMBER                  10

#define MAX_ROTATION_COUNT 96
#define MIN_ROTATION_COUNT 0

static bool is_initialized = false;

static struct GpioLine* line_A = NULL;
static struct GpioLine* line_B = NULL;

static struct GpioLine* button_line = NULL;

static atomic_int counter = 0;
static RotaryCallback clockwise_callback = NULL;
static RotaryCallback counter_clockwise_callback = NULL;
static RotaryCallback push_button_down_callback = NULL;

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
static pthread_t button_thread;

static pthread_mutex_t lock_thread = PTHREAD_MUTEX_INITIALIZER;

static bool stop_thread = false;
static bool is_button_down = false;

void RotaryStateMachine_register_clockwise_callback(RotaryCallback callback)
{
    clockwise_callback = callback;
}

void RotaryStateMachine_register_counter_clockwise_callback(RotaryCallback callback)
{
    counter_clockwise_callback = callback;
}

void RotaryStateMachine_register_push_button_down_callback(RotaryCallback callback)
{
    push_button_down_callback = callback;
}

/*
    START STATEMACHINE
*/
static void on_clockwise(void)
{
    counter++;
    
    if (clockwise_callback != NULL)
        clockwise_callback();
}

static void on_counter_clockwise(void)
{
    counter--;
    
    if (counter_clockwise_callback != NULL)
        counter_clockwise_callback();
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
    assert(is_initialized);
    
    (void)arg; // This is not being used, without this, getting unused parameter.
    while (!stop_thread) {
        struct gpiod_line_bulk bulkEvents;
        int numEvents = Gpio_waitForLinesChange(line_A, line_B, &bulkEvents);
        
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

static void* button_listener_thread(void *arg)
{
    (void)arg; // prevents arg not used error.
    
    bool prevState = false;
    while (!stop_thread) {
        struct gpiod_line_bulk bulkEvents;
        int numEvents = Gpio_waitForLineChange(button_line, &bulkEvents);
        if (numEvents < 0) {
            perror("Rotary button thread: Error waiting for line change");
            continue;
        }

        for (int i = 0; i < numEvents; i++) {
            struct gpiod_line *line_handle = gpiod_line_bulk_get_line(&bulkEvents, i);
            struct gpiod_line_event event;
            if (gpiod_line_event_read(line_handle, &event) == -1) {
                perror("Rotary button thread: Error reading event");
                continue;
            }
            // Falling edge: a press, rising: not pressed.
            bool isRising = (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE);

            pthread_mutex_lock(&lock_thread);
            is_button_down = !isRising;

            // Trigger a callback when prevState is falling (pressed) then currentState rising (released)
            if (!prevState && isRising && push_button_down_callback != NULL)
                push_button_down_callback();

            prevState = isRising;
            pthread_mutex_unlock(&lock_thread);
        }
    }

    return NULL;
}

bool RotaryStateMachine_is_button_down()
{
    // Ensure joystick is initialized.
    assert(is_initialized);

    pthread_mutex_lock(&lock_thread);
    bool is_down = is_button_down;

    pthread_mutex_unlock(&lock_thread);

    return is_down;
}

void RotaryStateMachine_init(void)
{
    printf("RotaryStateMachine - Initializing\n");
    
    assert(!is_initialized);

    line_A = Gpio_openForEvents(GPIO_LINE_A_CHIP, GPIO_LINE_A_NUMBER);
    line_B = Gpio_openForEvents(GPIO_LINE_B_CHIP, GPIO_LINE_B_NUMBER);

    pthread_mutex_init(&lock_thread, NULL);

    stop_thread = false;
    is_initialized = true;

    if (pthread_create(&event_thread, NULL, listen_for_events, NULL) != 0) {
        perror("RotaryStateMachine_init: Failed to create the event thread.");
        exit(EXIT_FAILURE);
    }

    button_line = Gpio_openForEvents(GPIO_BUTTON_CHIP, GPIO_BUTTON_NUMBER);
    if (!button_line) {
        perror("RotaryStateMachine_init: Failed to open button GPIO line");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&button_thread, NULL, button_listener_thread, NULL) != 0) {
        perror("Joystick_init: Failed to create button thread.");
        exit(EXIT_FAILURE);
    }
}

void RotaryStateMachine_cleanup(void)
{
    printf("RotaryStateMachine - Cleanup\n");

    assert(is_initialized);
    is_initialized = false;
    stop_thread = true;
    
    // Cancel event thread to break out of blocking call: Gpio_waitForLineChange
    pthread_cancel(event_thread);
    pthread_join(event_thread, NULL);
    
    pthread_mutex_destroy(&lock_thread);

    Gpio_close(line_A);
    Gpio_close(line_B);

    printf("RotaryStateMachine - Done.\n");
}