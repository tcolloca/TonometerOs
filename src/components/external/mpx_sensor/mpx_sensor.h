/*
 * DRIVER FOR THE MPX SENSOR THAT GOES OUTSIDE OF THE TONOMETER.
 */
#ifndef COMPONENTS_EXTERNAL_MPX_SENSOR_MPX_SENSOR_H_
#define COMPONENTS_EXTERNAL_MPX_SENSOR_MPX_SENSOR_H_

#include <stdint.h>

/* Initialize the driver. */
void MpxSensor_Init(char port, uint8_t pin_number);

/* Gets a pressure sample (mmHg x 100) from the Mpx Sensor. */
uint32_t MpxSensor_GetPressure();

#endif  // COMPONENTS_EXTERNAL_MPX_SENSOR_MPX_SENSOR_H_
