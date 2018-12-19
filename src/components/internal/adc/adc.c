#include "components/internal/adc/adc.h"

#include <avr/io.h>
#include <stdint.h>

#include "logger/logger.h"
#include "util/util.h"

void Adc_Init() {
	/* ADC Multiplexer Selection Register */

	SET(ADMUX, REFS0); 	// Set voltage reference to AVCC.
	// ADC channel 0.

	/* ADC Control and Status Registers */

	// Prescaler frequency = 109 KHz
	SET(ADCSRA, ADPS0);
	SET(ADCSRA, ADPS1);
	SET(ADCSRA, ADPS2);

//	CLEAR(ADCSRA, ADFR); // Disable free running mode

	SET(ADCSRA, ADEN);  // Enable ADC.

	Logger_AtDebug("Initialized ADC.");
}

uint16_t Adc_GetSample() {
	SET(ADCSRA, ADSC);  // Start conversion.

	while (IS_SET(ADCSRA, ADSC))
		;  // Wait until conversion is over.

	Logger_AtFinest("Got ADC Sample: %d", ADC);

	return ADC;
}
