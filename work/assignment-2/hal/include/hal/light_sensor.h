#ifndef _LightSensor_H_
#define _LightSensor_H_

#include <stdint.h>

void LightSensor_init(void);
uint16_t LightSensor_read_raw(void);
float LightSensor_read_voltage(void);
void LightSensor_cleanup(void);

#endif
