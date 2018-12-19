/*
 * DRIVER FOR THE AIR PUMP.
 */
#ifndef COMPONENTS_EXTERNAL_AIR_PUMP_AIR_PUMP_H_
#define COMPONENTS_EXTERNAL_AIR_PUMP_AIR_PUMP_H_

#include <stdint.h>

/* Initialize the driver. */
void AirPump_Init(char port, uint8_t pin_number);

/* Turns on the air pump. */
void AirPump_TurnOn();

/* Turns off the air pump. */
void AirPump_TurnOff();

#endif  // COMPONENTS_EXTERNAL_AIR_PUMP_AIR_PUMP_H_
