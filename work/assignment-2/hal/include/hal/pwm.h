// Part of the Hardware Abstraction Layer (HAL) 
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
