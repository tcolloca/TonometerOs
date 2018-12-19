#include "components/external/air_pump/air_pump.h"

#include <avr/io.h>
#include <stdint.h>

#include "components/internal/gpio/gpio.h"
#include "logger/logger.h"
#include "util/util.h"

static char port_;
static uint8_t pin_number_;

void AirPump_Init(char port, uint8_t pin_number) {
	Gpio_InitPin(port, pin_number, true);
	port_ = port;
	pin_number_ = pin_number;
	Logger_AtDebug("Initialized Air Pump at port %c%d", port_, pin_number_);
}

void AirPump_TurnOn() {
	Gpio_SetPin(port_, pin_number_);
	Logger_AtInfo("Air Pump turned on.");
}

void AirPump_TurnOff() {
	Gpio_ClearPin(port_, pin_number_);
	Logger_AtInfo("Air Pump turned off.");
}

