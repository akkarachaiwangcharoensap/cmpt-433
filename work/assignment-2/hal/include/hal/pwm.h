// Part of the Hardware Abstraction Layer (HAL) 
#ifndef _PWM_H_
#define _PWM_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void Pwm_init(void);

void Pwm_turn_on(void);
void Pwm_turn_off(void);

bool Pwm_is_on(void);
bool Pwm_is_off(void);

void Pwm_flash(void);
void Pwm_set_flash_speed(float flashSpeed);

void Pwm_cleanup(void);

#endif
