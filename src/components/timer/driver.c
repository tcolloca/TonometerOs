#include "components/timer/driver.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "components/timer/event.h"
#include "error/error.h"
#include "util/util.h"

#define CLOCK_HZ         14745600
#define PRESCALER        1024
#define RESOLUTION_FREQ  100  // 100Hz = 1 / 100 s = 0.01 s = 10 ms

//#define PRESCALER        1024
//#define RESOLUTION_FREQ  10000  // 10000 Hz = 1 / 10000 s = 0.0001 s = 0.1 ms

static volatile uint64_t ticks_msec_ = 50000;
static uint64_t ticks_sec_ = 50;

static void Timer_HandleTick();

void Timer_Init() {
	CLEAR(TIMSK, OCIE0);  // Disable Timer/Counter0 Compare match interrupt.

	TCNT0 = 0;  // Reset counter.

	/* Set prescaler */
	char prescaler = 0;
	if (PRESCALER == 1024) {
		SET(prescaler, CS00);
		SET(prescaler, CS01);
		SET(prescaler, CS02);
	} else if (PRESCALER == 256) {
		CLEAR(prescaler, CS00);
		SET(prescaler, CS01);
		SET(prescaler, CS02);
	} else if (PRESCALER == 8) {
		CLEAR(prescaler, CS00);
		SET(prescaler, CS01);
		CLEAR(prescaler, CS02);
	} else {
		Error_SetError("Prescaler not defined.");
		return;
	}
	TCCR0 |= prescaler;

	/* Set compare value for given resolution frequency. */
	uint64_t pre_scaled_time = CLOCK_HZ / PRESCALER;
//	if (pre_scaled_time % RESOLUTION_FREQ != 0) {
//		Error_SetError(
//				"Pre-scaled time is not a multiple of the resolution frequency.");
//		return;
//	}
	OCR0 = pre_scaled_time / RESOLUTION_FREQ;  // Compare to this value.
//	 OCR0 = 28;

	/* Other control config */
	SET(TCCR0, WGM01);  // Use CTC mode.

	// While any of TCNT0, OCR0 or TCR0 are being updated, wait.
	while (IS_SET(ASSR, TCN0UB) || IS_SET(ASSR, OCR0UB) || IS_SET(ASSR, TCR0UB))
		;

	SET(TIMSK, OCIE0);  // Enable Timer/Counter0 Compare match interrupt.
}

/* Timer/Counter0 Interrupt */
SIGNAL(TIMER0_COMP_vect) {
	Timer_HandleTick();
	TimerEvent* event = TimerEvent_New(ticks_msec_);
	Dispatcher_Dispatch(TIMER_EVENT_ID, event);
	TimerEvent_Destroy(event);
}

unsigned int Timer_GetStartTimeInSecs() {
	return ticks_sec_;
}

unsigned int Timer_GetStartTimeInMillis() {
	return ticks_msec_;
}

void Timer_HandleTick() {
	ticks_msec_ += 10;
}
