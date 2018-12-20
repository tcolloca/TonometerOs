#include "components/internal/adc/adc.h"

#include <avr/io.h>
#include <stdint.h>

#include "logger/logger.h"
#include "util/util.h"

static void Adc_WaitForConversion();

static uint8_t channel_;

static void Adc_SetChannel(uint8_t channel);

void Adc_Init() {
	/* ADC Multiplexer Selection Register */

	SET(ADMUX, REFS0); 	// Set voltage reference to AVCC.

	/* ADC Control and Status Registers */

	// Prescaler frequency = 109 KHz
	SET(ADCSRA, ADPS0);
	SET(ADCSRA, ADPS1);
	SET(ADCSRA, ADPS2);

//	CLEAR(ADCSRA, ADFR); // Disable free running mode

	SET(ADCSRA, ADEN);// Enable ADC.

	Logger_AtDebug("Initialized ADC.");
}

static void Adc_SetChannel(uint8_t channel) {
	if (channel_ == channel) {
		return;
	}
	Adc_WaitForConversion();

	channel_ = channel;

	CLEAR_MASK(ADMUX, 0x07);
	SET_MASK(ADMUX, channel_);

	Logger_AtFinest("\tChanged ADC channel: %d", channel_);
	Logger_AtInfo("\tADMUX: %d", ADMUX);
}

uint16_t Adc_GetSample(uint8_t channel) {
	Logger_AtInfo("Getting sample from channel: %d ...", channel);

	Adc_SetChannel(channel);
	SET(ADCSRA, ADSC);  // Start conversion.

	Adc_WaitForConversion();

	SET(ADCSRA, ADSC);  // Start conversion.

	Adc_WaitForConversion();

	Logger_AtInfo("Got ADC Sample: %d", ADC);

	return ADC;
}

void Adc_WaitForConversion() {
	while (IS_SET(ADCSRA, ADSC))
		;  // Wait until conversion is over.
}
