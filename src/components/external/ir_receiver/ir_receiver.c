#include "components/external/ir_receiver/ir_receiver.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

#include "components/internal/adc/adc.h"
#include "components/internal/gpio/gpio.h"
#include "logger/logger.h"
#include "util/util.h"

#define DELAY_US 1000

static char port_;
static uint8_t pin_number_;

static uint16_t IrReceiver_MedianOfFive(uint16_t n1, uint16_t n2, uint16_t n3,
		uint16_t n4, uint16_t n5);

void IrReceiver_Init(char port, uint8_t pin_number) {
	if (port != 'F' && port != 'f') {
		Logger_AtError("Invalid port. "
				"IR Receiver should be set in a Port F (ADC).");
	}
	Gpio_InitPin(port, pin_number, /* output = */false);
	port_ = port;
	pin_number_ = pin_number;
	Logger_AtDebug("Initialized IR Receiver at port %c%d", port_, pin_number_);
}

uint16_t IrReceiver_GetSample() {
	Logger_AtFiner("Getting sample from IR Receiver...");
	uint16_t data1 = Adc_GetSampleMaybeDisard(pin_number_, /* discard_first = */
			false);
	uint16_t data2 = Adc_GetSampleMaybeDisard(pin_number_, /* discard_first = */
			false);
	uint16_t data3 = Adc_GetSampleMaybeDisard(pin_number_, /* discard_first = */
			false);
	uint16_t data4 = Adc_GetSampleMaybeDisard(pin_number_, /* discard_first = */
			false);
	uint16_t data5 = Adc_GetSampleMaybeDisard(pin_number_, /* discard_first = */
			false);

	uint16_t data_med = IrReceiver_MedianOfFive(data1, data2, data3, data4,
			data5);

	Logger_AtDebug("Got sample from IR Receiver: %d", data_med);
	return data_med;
}

uint16_t IrReceiver_MedianOfFive(uint16_t n1, uint16_t n2, uint16_t n3,
		uint16_t n4, uint16_t n5) {
	uint16_t *a = &n1, *b = &n2, *c = &n3, *d = &n4, *e = &n5;
	uint16_t *tmp;

	// makes a < b and b < d
	if (*b < *a) {
		tmp = a;
		a = b;
		b = tmp;
	}

	if (*d < *c) {
		tmp = c;
		c = d;
		d = tmp;
	}

	// eleminate the lowest
	if (*c < *a) {
		tmp = b;
		b = d;
		d = tmp;
		c = a;
	}

	// gets e in
	a = e;

	// makes a < b and b < d
	if (*b < *a) {
		tmp = a;
		a = b;
		b = tmp;
	}

	// eliminate another lowest
	// remaing: a,b,d
	if (*a < *c) {
		tmp = b;
		b = d;
		d = tmp;
		a = c;
	}

	if (*d < *a)
		return *d;
	else
		return *a;

}

