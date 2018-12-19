/*
 * TIMER EVENT API.
 */
#ifndef COMPONENTS_INTERNAL_TIMER_EVENT_H_
#define COMPONENTS_INTERNAL_TIMER_EVENT_H_

#include <stdint.h>

#include "event/event.h"

typedef struct TimerEvent TimerEvent;

void Timer_AddListener(void* self, Listener* listener);

TimerEvent* TimerEvent_New(uint64_t ticks);

void TimerEvent_Destroy(TimerEvent* self);

uint64_t TimerEvent_GetTicks(TimerEvent* event);

#endif  // COMPONENTS_INTERNAL_TIMER_EVENT_H_
