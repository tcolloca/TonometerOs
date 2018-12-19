/*
 * DRIVER FOR THE IR LED.
 */
#ifndef COMPONENTS_EXTERNAL_IR_LED_IR_LED_H_
#define COMPONENTS_EXTERNAL_IR_LED_IR_LED_H_

#include <stdint.h>

/* Initialize the driver. */
void IrLed_Init(char port, uint8_t pin_number);

/* Turns on the IR led. */
void IrLed_TurnOn();

/* Turns off the IR led. */
void IrLed_TurnOff();

#endif  // COMPONENTS_EXTERNAL_IR_LED_IR_LED_H_
