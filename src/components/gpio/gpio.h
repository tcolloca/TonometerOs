/*
 * DRIVER FOR THE INTERNAL LED USING PORT B7.
 */
#ifndef COMPONENTS_GPIO_GPIO_H_
#define COMPONENTS_GPIO_GPIO_H_

#include <stdbool.h>
#include <stdint.h>

/* Initialize the given pin for the port as either input or output. */
void Gpio_InitPin(char port, uint8_t pin_number, bool output);

/* Initialize all the pins for the port as either input or output. */
void Gpio_InitAll(char port, bool output);

/* Initialize pins for the given mask and port as either input or output. */
void Gpio_InitWithMask(char port, uint8_t mask, bool output);

/* Set the given pin. */
void Gpio_SetPin(char port, uint8_t pin_number);

/* Set the pins of the port using the given mask. */
void Gpio_SetMask(char port, uint8_t mask);

/* Clear the given pin. */
void Gpio_ClearPin(char port, uint8_t pin_number);

/* Clear the pins of the port using the given mask. */
void Gpio_ClearMask(char port, uint8_t mask);

/* Read pin value. */
bool Gpio_ReadPin(char port, uint8_t pin_number);

/* Read all pins from port. */
uint8_t Gpio_ReadAll(char port);

/* Read pins from port using the given mask. */
uint8_t Gpio_ReadWithMask(char port, uint8_t mask);

#endif  // COMPONENTS_GPIO_GPIO_H_
