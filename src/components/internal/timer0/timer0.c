#include "components/internal/timer0/timer0.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

#include "components/internal/led/led.h" // TODO: Remove
#include "logger/logger.h"
#include "util/util.h"

#define CLOCK_HZ         14745600
#define PRESCALER        8
#define RESOLUTION_FREQ  50000  // 50000 Hz = 1 / 50000 s = 0.00002 s = 0.02 ms

static const int DELTA_USECS_ = 1000000 / RESOLUTION_FREQ;

static volatile uint64_t ticks_usecs_ = 0;

static uint8_t Timer0_SetPrescaler();

void Timer0_Init() {
	CLEAR(TIMSK, OCIE0);  // Disable Timer/Counter0 Compare match interrupt.

	TCNT0 = 0;  // Reset counter.

	Timer0_SetPrescaler();

	OCR0 = CLOCK_HZ / PRESCALER / RESOLUTION_FREQ - 1;  // Compare to this value.

	/* Other control config */
	SET(TCCR0, WGM01);  // Use CTC mode.

	// While any of TCNT0, OCR0 or TCR0 are being updated, wait.
	while (IS_SET(ASSR, TCN0UB) || IS_SET(ASSR, OCR0UB) || IS_SET(ASSR, TCR0UB))
		;

	SET(TIMSK, OCIE0);  // Enable Timer/Counter0 Compare match interrupt.

//	Logger_AtDebug("Initialized Timer0 at CTC mode.");
//	Logger_AtDebug("Initialized Timer0 Prescaler: %d", PRESCALER);
//	Logger_AtDebug("Initialized Timer0 OCR0: %d", OCR0);
}

/* Timer/Counter0 Interrupt */
SIGNAL(TIMER0_COMP_vect) {
	ticks_usecs_ += DELTA_USECS_;
}

uint8_t Timer0_SetPrescaler() {
	uint8_t prescaler = 0;
	if (PRESCALER == 0) {           // 000
		// No clock source.
	} else if (PRESCALER == 1) {    // 001
		SET(prescaler, CS00);
	} else if (PRESCALER == 8) {    // 010
		SET(prescaler, CS01);
	} else if (PRESCALER == 32) {   // 011
		SET(prescaler, CS00);
		SET(prescaler, CS01);
	} else if (PRESCALER == 64) {   // 100
		SET(prescaler, CS02);
	} else if (PRESCALER == 128) {  // 101
		SET(prescaler, CS00);
		SET(prescaler, CS02);
	} else if (PRESCALER == 256) {  // 110
		SET(prescaler, CS01);
		SET(prescaler, CS02);
	} else if (PRESCALER == 1024) { // 111
		SET(prescaler, CS00);
		SET(prescaler, CS01);
		SET(prescaler, CS02);
	} else {
//		Logger_AtError("Timer0 prescaler not defined.");
		return 0;
	}
	TCCR0 |= prescaler;
	return prescaler;
}

uint64_t Timer0_GetStartTimeInMillis() {
	return ticks_usecs_ / 1000;
}

uint64_t Timer0_GetStartTimeInMicros() {
	return ticks_usecs_;
}
