#include "components/internal/adc/event.h"

#include "event/event.h"
#include "lib/memory.h"
#include "util/util.h"

struct AdcReadEvent {
	int data_;
};

void AdcRead_AddListener(void* self, Listener* listener) {
	Dispatcher_AddListener(ADC_READ_EVENT_ID, listener);
}

AdcReadEvent* AdcReadEvent_New(int data) {
	AdcReadEvent* event = NEW(AdcReadEvent);
	event->data_ = data;
	return event;
}

void AdcReadEvent_Destroy(AdcReadEvent* self) {
	FREE(self);
}

int AdcReadEvent_GetData(AdcReadEvent* event) {
	return event->data_;
}
