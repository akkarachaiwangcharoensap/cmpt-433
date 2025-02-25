// The PWM module manages a PWM (Pulse-Width Modulation) device on a specific hardware interface (GPIO12). 
// It includes functions to initialize the PWM system, configure its operating frequency.
// Additionally, it offers an ability to increase or decrease the frequency (within a 0–500 Hz range) 
// and perform proper cleanup when the PWM is no longer needed.
#ifndef _PWM_H_
#define _PWM_H_

void Pwm_init(void);

void Pwm_turn_on(void);
void Pwm_turn_off(void);

int Pwm_get_frequency(void);
void Pwm_set_frequency(int frequency);

void Pwm_increase_frequency(void);
void Pwm_decrease_frequency(void);

void Pwm_cleanup(void);

#endif
