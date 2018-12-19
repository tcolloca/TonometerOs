#include "components/internal/timer1/timer1.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "components/internal/led/led.h" // TODO: Remove.
#include "logger/logger.h"
#include "util/util.h"

#define CLOCK_HZ         14745600
#define PRESCALER        1024
// 1000 Hz seems to be the maximum freq.
#define RESOLUTION_FREQ  100  // 100 Hz = 1 / 100 s = 0.01 s = 10 ms

static const int DELTA_USECS_ = 1000000 / RESOLUTION_FREQ;
static const int DELTA_MSECS_ = 1000 / RESOLUTION_FREQ;

static volatile uint64_t ticks_usecs_ = 0;
static volatile uint64_t ticks_msecs_ = 0;

static uint8_t Timer1_SetPrescaler();

void Timer1_Init() {
	CLEAR(TIMSK, OCIE1A);  // Disable Timer/Counter1 Compare match interrupt.

	TCNT1 = 0;  // Reset counter.

	uint8_t prescaler = Timer1_SetPrescaler();

	OCR1A = CLOCK_HZ / PRESCALER / RESOLUTION_FREQ - 1;  // Compare to this value.

	/* Other control config */
	SET(TCCR1B, WGM12);  // Use CTC mode.

	SET(TIMSK, OCIE1A);  // Enable Timer/Counter0 Compare match interrupt.

	Logger_AtDebug("Initialized Timer1 at CTC mode (Match A).");
	Logger_AtDebug("Initialized Timer1 Prescaler: %d", prescaler);
	Logger_AtDebug("Initialized Timer1 OCR1A: %d", OCR1A);
}

/* Timer/Counter1 Interrupt */
SIGNAL(TIMER1_COMPA_vect	) {
	ticks_usecs_ += DELTA_USECS_;
	ticks_msecs_ += DELTA_MSECS_;
	if (DELTA_MSECS_ == 0) {
		ticks_msecs_ = ticks_usecs_ / 1000;
	}
}

uint8_t Timer1_SetPrescaler() {
	char prescaler = 0;
	if (PRESCALER == 0) {           // 000
		// No clock source.
	} else if (PRESCALER == 1) {     // 001
		SET(prescaler, CS10);
	} else if (PRESCALER == 8) {     // 010
		SET(prescaler, CS11);
	} else if (PRESCALER == 64) {    // 011
		SET(prescaler, CS10);
		SET(prescaler, CS11);
	} else if (PRESCALER == 256) {   // 100
		SET(prescaler, CS12);
	} else if (PRESCALER == 1024) {  // 101
		SET(prescaler, CS10);
		SET(prescaler, CS12);
	} else {
		Logger_AtError("Timer1 prescaler not defined.");
		return prescaler;
	}
	TCCR1B |= prescaler;
	return prescaler;
}

uint64_t Timer1_GetStartTimeInMillis() {
	return ticks_msecs_;
}

