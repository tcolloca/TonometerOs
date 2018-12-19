/*
 * DRIVER FOR THE INTERNAL LED USING PORT B7.
 */
#ifndef COMPONENTS_INTERNAL_LED_LED_H_
#define COMPONENTS_INTERNAL_LED_LED_H_

/* Initialize the driver. */
void Led_Init();

/* Turns on the internal led. */
void Led_TurnOn();

/* Turns off the internal led. */
void Led_TurnOff();

#endif  // COMPONENTS_INTERNAL_LED_LED_H_
