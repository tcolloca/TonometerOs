#include <avr/io.h>
#include <avr/interrupt.h>
#include <components/internal/pwm/pwm.h>
#include <stdint.h>

#include "logger/logger.h"
#include "util/util.h"

#define PRESCALER 1

static uint8_t duty_cycle_ = 5;

void Pwm_Init() {
	CLEAR(TIMSK, OCIE2);  // Disable Timer/Counter2 Compare match interrupt.

	/* Set Fast PWM mode */
	SET(TCCR2, WGM21);
	SET(TCCR2, WGM20);

	SET(TCCR2, COM21);  // Set OC2 non-inverting mode

	TCNT2 = 0;  // Reset counter

	/* Set prescaler */
	char prescaler = 0;
	if (PRESCALER == 1) {
		SET(prescaler, CS20);
	} else {
		Logger_AtError("Prescaler not defined.");
		return;
	}
	TCCR2 |= prescaler;

	Pwm_SetDutyCycle(duty_cycle_);

	SET(DDRB, PB7);  // Set OC2 = PB7 as output.

	//	SET(TIMSK, OCIE2);  // Enable Output Compare Match Interrupt

	Logger_AtDebug("Initialized Timer2 at PWM mode.");
	Logger_AtDebug("Initialized Timer2 Prescaler: %d", prescaler);
	Logger_AtDebug("Initialized Timer2 OCR2 (duty cycle): %d", OCR2);
}

uint8_t Pwm_GetDutyCycle() {
	return duty_cycle_;
}

void Pwm_SetDutyCycle(uint8_t duty_cycle) {
//	CLEAR(TIMSK, OCIE2);  // Disable Timer/Counter2 Compare match interrupt.

	duty_cycle_ = duty_cycle;
	OCR2 = 256 * duty_cycle_ / 100;  // Set duty cycle

//	SET(TIMSK, OCIE2);  // Enable Output Compare Match Interrupt
}

/* Timer/Counter2 Interrupt */
SIGNAL(TIMER2_COMP_vect) {
  return;
}

