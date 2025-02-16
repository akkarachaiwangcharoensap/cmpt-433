#ifndef _ROTARY_STATEMACHINE_H_
#define _ROTARY_STATEMACHINE_H_

// Reference: lecture slides.
#include <stdbool.h>

void RotaryStateMachine_init(void);
void RotaryStateMachine_cleanup(void);

int RotaryStateMachine_getValue(void);

// TODO: This should be on a background thread (internal?)
// void RotaryStateMachine_doState();

#endif