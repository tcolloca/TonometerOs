/*
 * DRIVER FOR PWM USING TIMER/COUNTER2.
 */
#ifndef COMPONENTS_INTERNAL_PWM_PWM_H_
#define COMPONENTS_INTERNAL_PWM_PWM_H_

#include <stdint.h>

/* Initialize PWM. */
void Pwm_Init();

/* Get duty cycle. */
uint8_t Pwm_GetDutyCycle();

/* Set duty cycle. */
void Pwm_SetDutyCycle(uint8_t duty_cycle);

#endif  // COMPONENTS_INTERNAL_PWM_PWM_H_
