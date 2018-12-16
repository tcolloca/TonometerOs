/*
 * DRIVER FOR PWM USING TIMER/COUNTER2.
 */
#ifndef COMPONENTS_PWM_DRIVER_H_
#define COMPONENTS_PWM_DRIVER_H_

void Pwm_Init();

double Pwm_GetDutyCycle();

void Pwm_SetDutyCycle(double duty_cycle);

#endif  // COMPONENTS_PWM_DRIVER_H_
