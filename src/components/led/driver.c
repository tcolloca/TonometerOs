#include "components/led/driver.h"

#include <avr/io.h>

#include "components/gpio/gpio.h"
#include "util/util.h"

#define LED_PIN  PB7

void Led_Init() {
	Gpio_InitPin('B', LED_PIN, true /* output */);
}

void Led_TurnOff() {
	Gpio_SetPin('B', LED_PIN);
}

void Led_TurnOn() {
	Gpio_ClearPin('B', LED_PIN);
}
