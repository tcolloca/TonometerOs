#include "components/external/ir_receiver/ir_receiver.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#include "components/internal/adc/adc.h"
#include "components/internal/gpio/gpio.h"
#include "logger/logger.h"
#include "util/util.h"

static char port_;
static uint8_t pin_number_;

void IrReceiver_Init(char port, uint8_t pin_number) {
	if (port != 'F' && port != 'f') {
		Logger_AtError("Invalid port. "
				"IR Receiver should be set in a Port F (ADC).");
	}
	Gpio_InitPin(port, pin_number, /* output = */ false);
	port_ = port;
	pin_number_ = pin_number;
	Logger_AtDebug("Initialized IR Receiver at port %c%d", port_, pin_number_);
}

uint16_t IrReceiver_GetSample() {
	Logger_AtDebug("Getting sample from IR Receiver...");
	uint16_t data = Adc_GetSample(pin_number_);
	Logger_AtDebug("Got sample from IR Receiver: %d", data);
	return data;
}

