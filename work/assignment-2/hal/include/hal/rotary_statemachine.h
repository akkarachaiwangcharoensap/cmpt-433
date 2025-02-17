#ifndef _ROTARY_STATEMACHINE_H_
#define _ROTARY_STATEMACHINE_H_

// Reference: lecture slides.
#include <stdbool.h>

// Normalized: [0, 1]
typedef void (*RotaryCallback)(double normalized);
void RotaryStateMachine_init(void);
void RotaryStateMachine_cleanup(void);

int RotaryStateMachine_getValue(void);
void RotaryStateMachine_registerCallback(RotaryCallback callback);

// TODO: This should be on a background thread (internal?)
// void RotaryStateMachine_doState();

#endif