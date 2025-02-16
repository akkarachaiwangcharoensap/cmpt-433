// Part of the Hardware Abstraction Layer (HAL) 
#ifndef _LED_H_
#define _LED_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef enum {
    Led_Red,
    Led_Green
} Led_Color;


// Hide LED members (encapsulation). (https://stackoverflow.com/questions/5368028/how-to-make-struct-members-private)
typedef struct Led Led;

Led* Led_init(Led_Color color);

void Led_turn_on(Led *led);
void Led_turn_off(Led *led);

bool Led_is_on(Led *led);
bool Led_is_off(Led *led);

void Led_flash(Led *led);

void Led_cleanup(Led *led);

#endif
