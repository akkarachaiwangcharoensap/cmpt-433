/*
 * Provide an interface for an I2C-based accelerometer sensor.
 * It includes functions for initializing the sensor, reading raw data from the
 * X, Y, and Z axes, and normalizing these readings. It also supports
 * shake detection on each axis by monitoring changes in the normalized values,
 * with callback registration functions to notify when a shake event is detected.
 */
#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

typedef void (*AccelerometerCallback)(void);

void Accelerometer_init(void);

int16_t Accelerometer_getX(void);
int16_t Accelerometer_getY(void);
int16_t Accelerometer_getZ(void);

float Accelerometer_get_normalized_x_rotation(void);
float Accelerometer_get_normalized_y_rotation(void);

void Accelerometer_register_shake_x_callback(AccelerometerCallback callback);
void Accelerometer_register_shake_y_callback(AccelerometerCallback callback);
void Accelerometer_register_shake_z_callback(AccelerometerCallback callback);

bool Accelerometer_check_shake_x(void);
bool Accelerometer_check_shake_y(void);
bool Accelerometer_check_shake_z(void);

void Accelerometer_cleanup(void);

#endif
