#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdbool.h>
#include <unistd.h>

// Hide Joystick members (encapsulation). (https://stackoverflow.com/questions/5368028/how-to-make-struct-members-private)
typedef struct Joystick Joystick;

Joystick* Joystick_init();

float Joystick_read_vertical(Joystick *joystick);
float Joystick_read_horizontal(Joystick *joystick);

bool Joystick_is_up(Joystick *joystick);
bool Joystick_is_down(Joystick *joystick);

bool Joystick_is_left(Joystick *joystick);
bool Joystick_is_right(Joystick *joystick);

void Joystick_cleanup(Joystick *joystick);

#endif
