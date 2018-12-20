#include "components/external/mpx_sensor/mpx_sensor.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#include "components/internal/adc/adc.h"
#include "components/internal/gpio/gpio.h"
#include "logger/logger.h"
#include "util/util.h"

static char port_;
static uint8_t pin_number_;

void MpxSensor_Init(char port, uint8_t pin_number) {
	if (port != 'F' && port != 'f') {
		Logger_AtError("Invalid port. "
				"Mpx Sensor should be set in a Port F (ADC).");
	}
	Gpio_InitPin(port, pin_number, /* output = */ false);
	port_ = port;
	pin_number_ = pin_number;
	Logger_AtDebug("Initialized Mpx Sensor at port %c%d", port_, pin_number_);
}

uint32_t MpxSensor_GetPressure() {
	Logger_AtDebug("Getting sample from Mpx Sensor...");
	uint16_t data = Adc_GetSample(pin_number_);
	Logger_AtInfo("Got sample from Mpx Sensor: %d", data);

	uint32_t millivolts = 5 * 1000 / 1023 * data;

	Logger_AtInfo("mV: %lu", millivolts);


//	uint32_t m = (400000 - 20000) / (4800 - 200);

//	Logger_AtInfo("m: %lu", m);


//	uint32_t b = (20000) - m * 200;

//	Logger_AtInfo("b: %lu", b);

		uint32_t pressure_hpa = (millivolts * 1000 + (double) 42.1) * (double) 413.052457662 / 5 / 100;
//  uint32_t pressure_hpa = m * millivolts + b;
//	uint32_t pressure_hpa = (420000 - 0) * data / 1023 + 0;

	Logger_AtInfo("MPX Pressure (hPa x 100): %lu", pressure_hpa);

	uint64_t pressure_mmHg = (uint64_t) (0.7500616827 * (double) pressure_hpa);

	return pressure_mmHg;
}

