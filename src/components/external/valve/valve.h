/*
 * DRIVER FOR THE VALVE.
 */
#ifndef COMPONENTS_EXTERNAL_VALVE_VALVE_H_
#define COMPONENTS_EXTERNAL_VALVE_VALVE_H_

#include <stdint.h>

/* Initialize the driver. */
void Valve_Init(char port, uint8_t pin_number);

/* Opens the valve. */
void Valve_Open();

/* Closes the valve. */
void Valve_Close();

#endif  // COMPONENTS_EXTERNAL_VALVE_VALVE_H_
