#include "components/valve/valve.h"

#include <avr/io.h>
#include <stdint.h>

#include "components/gpio/gpio.h"
#include "util/util.h"

static char port_;
static uint8_t pin_number_;

void Valve_Init(char port, uint8_t pin_number) {
	Gpio_InitPin(port, pin_number, true);
	port_ = port;
	pin_number_ = pin_number;
}

void Valve_TurnOn() {
	Gpio_SetPin(port_, pin_number_);
}

void Valve_TurnOff() {
	Gpio_ClearPin(port_, pin_number_);
}

