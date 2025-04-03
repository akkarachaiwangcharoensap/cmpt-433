// The RotaryStateMachine module implements a rotary encoder state machine. 
// It monitors two GPIO lines corresponding to the encoder’s signals (A and B)
// and uses a 4-states machine to determine the direction of rotation. 
// When a rising or falling edge is detected on either GPIO line, 
// the state machine transitions, updates an internal counter, 
// and invokes any registered callback for either a clockwise or counterclockwise turn.
// It also now support push button down callback.
#ifndef _ROTARY_STATEMACHINE_H_
#define _ROTARY_STATEMACHINE_H_

#include <stdbool.h>

typedef void (*RotaryCallback)(void);

void RotaryStateMachine_init(void);
void RotaryStateMachine_cleanup(void);

int RotaryStateMachine_getValue(void);
bool RotaryStateMachine_is_button_down();

void RotaryStateMachine_register_clockwise_callback(RotaryCallback callback);
void RotaryStateMachine_register_counter_clockwise_callback(RotaryCallback callback);
void RotaryStateMachine_register_push_button_down_callback(RotaryCallback callback);

#endif