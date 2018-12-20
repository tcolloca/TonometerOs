#include "components/internal/led/led.h"

#include <avr/io.h>

#include "components/internal/gpio/gpio.h"
#include "logger/logger.h"
#include "util/util.h"

#define LED_PIN  PB7

void Led_Init() {
	Gpio_InitPin('B', LED_PIN, /* output = */ true);
//	Logger_AtDebug("Initialized Internal Led at port B%d", LED_PIN);
}

void Led_TurnOff() {
	// Internal Led power is opposite to pin value.
	Gpio_SetPin('B', LED_PIN);
//	Logger_AtFinest("Internal Led off.");
}

void Led_TurnOn() {
	Gpio_ClearPin('B', LED_PIN);
//	Logger_AtFinest("Internal Led on.");
}
