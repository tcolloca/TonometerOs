#include "components/timer/event.h"

#include <stdint.h>

#include "event/event.h"
#include "lib/memory.h"
#include "util/util.h"

struct TimerEvent {
	uint64_t ticks_;
};

void Timer_AddListener(void* self, Listener* listener) {
	Dispatcher_AddListener(TIMER_EVENT_ID, listener);
}

TimerEvent* TimerEvent_New(uint64_t ticks) {
	TimerEvent* event = NEW(TimerEvent);
	event->ticks_ = ticks;
	return event;
}

void TimerEvent_Destroy(TimerEvent* self) {
	FREE(self);
}

uint64_t TimerEvent_GetTicks(TimerEvent* event) {
	return event->ticks_;
}
