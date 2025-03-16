/*
 * Provide an interface for interacting with a joystick device.
 * This includes functions that: 
 * 1.) Initialize and cleanup the joystick hardware and related threads.
 * 2.) Read normalized vertical and horizontal joystick positions (range -1 to 1).
 * 3.) Determine directional movement (up, down, left, right) based on a configurable sensitivity.
 * 4.) Detect push button state and register callback functions for button press events.
 */
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdbool.h>
#include <unistd.h>

typedef void (*JoystickCallback)(void);

void Joystick_init(void);

float Joystick_read_vertical(void);
float Joystick_read_horizontal(void);

bool Joystick_is_up(void);
bool Joystick_is_down(void);

bool Joystick_is_left(void);
bool Joystick_is_right(void);

bool Joystick_is_push_button_down(void);

void Joystick_register_pressed_up_callback(JoystickCallback callback);
void Joystick_register_pressed_down_callback(JoystickCallback callback);
void Joystick_register_push_button_down_callback(JoystickCallback callback);

void Joystick_cleanup(void);

#endif
