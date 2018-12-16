/*
 * DRIVER FOR TIMER/COUNTER0
 */
#ifndef COMPONENTS_TIMER_DRIVER_H_
#define COMPONENTS_TIMER_DRIVER_H_

/* Initialize driver. */
void Timer_Init();

/* Returns time since start time in seconds. */
unsigned int Timer_GetStartTimeInSecs();

/* Returns time since start time in milliseconds. */
unsigned int Timer_GetStartTimeInMillis();

#endif  // COMPONENTS_TIMER_DRIVER_H_
