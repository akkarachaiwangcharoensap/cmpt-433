// The LightSensor module communicates with an ADC (TLA2024) over the I2C bus on a Linux system. 
// It initializes the I2C interface and sets up the sensor configuration, 
// then creates a separate thread that continuously reads the sensor’s raw data. 
// The module provides functions to return the raw ADC value and convert that value into voltage.
#ifndef _LightSensor_H_
#define _LightSensor_H_

#include <stdint.h>

void LightSensor_init(void);
uint16_t LightSensor_read_raw(void);
float LightSensor_read_voltage(void);
void LightSensor_cleanup(void);

#endif
