/*
 * DRIVER FOR TIMER/COUNTER1
 */
#ifndef COMPONENTS_INTERNAL_TIMER1_TIMER1_H_
#define COMPONENTS_INTERNAL_TIMER1_TIMER1_H_

#include <stdint.h>

/* Initialize driver. */
void Timer1_Init();

/* Returns time since start time in milliseconds. */
uint64_t Timer1_GetStartTimeInMillis();

#endif  // COMPONENTS_INTERNAL_TIMER1_TIMER1_H_
