#ifndef _LightSensor_H_
#define _LightSensor_H_

#include <stdbool.h>
#include <unistd.h>

void LightSensor_init(void);
float LightSensor_read_light(void);
void LightSensor_cleanup(void);

#endif
