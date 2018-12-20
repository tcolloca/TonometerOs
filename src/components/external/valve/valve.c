#include "components/external/valve/valve.h"

#include <avr/io.h>
#include <stdint.h>

#include "components/internal/gpio/gpio.h"
#include "logger/logger.h"
#include "util/util.h"

static char port_;
static uint8_t pin_number_;

void Valve_Init(char port, uint8_t pin_number) {
	Gpio_InitPin(port, pin_number, /* output = */ true);
	port_ = port;
	pin_number_ = pin_number;
	Logger_AtDebug("Initialized Valve at port %c%d", port_, pin_number_);
}

void Valve_Open() {
	Gpio_SetPin(port_, pin_number_);
	Logger_AtDebug("Opened Valve.");
}

void Valve_Close() {
	Gpio_ClearPin(port_, pin_number_);
	Logger_AtDebug("Closed Valve.");
}

