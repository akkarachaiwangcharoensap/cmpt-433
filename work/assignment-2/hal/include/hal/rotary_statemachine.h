#ifndef _ROTARY_STATEMACHINE_H_
#define _ROTARY_STATEMACHINE_H_

typedef void (*RotaryCallback)(void);

void RotaryStateMachine_init(void);
void RotaryStateMachine_cleanup(void);

int RotaryStateMachine_getValue(void);

void RotaryStateMachine_registerClockwiseCallback(RotaryCallback callback);
void RotaryStateMachine_registerCounterClockwiseCallback(RotaryCallback callback);

#endif