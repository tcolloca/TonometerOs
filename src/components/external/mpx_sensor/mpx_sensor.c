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
	Logger_AtDebug("Got sample from Mpx Sensor: %d", data);

	float pressure_kpa = (data/(float)1023+0.00842)/ (float)0.002421;

	Logger_AtDebug("Pressure kPa x100: %d", (uint32_t) (pressure_kpa * 100));

	uint64_t aux = (uint64_t) (7.500616827 * (double) pressure_kpa);

	uint64_t pressure_mmHg = aux < 760 ? 0 : aux - 760;

	return pressure_mmHg;
}

