/*
 * DRIVER FOR TIMER/COUNTER0
 */
#ifndef COMPONENTS_INTERNAL_TIMER0_TIMER0_H_
#define COMPONENTS_INTERNAL_TIMER0_TIMER0_H_

#include <stdint.h>

/* Initialize driver. */
void Timer0_Init();

/* Returns time since start time in milliseconds. */
uint64_t Timer0_GetStartTimeInMillis();

uint64_t Timer0_GetStartTimeInMicros();

#endif  // COMPONENTS_INTERNAL_TIMER0_TIMER0_H_
