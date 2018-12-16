#include "components/usb/event.h"

#include "event/event.h"
#include "lib/memory.h"
#include "util/util.h"

struct UsbReadEvent {
	unsigned char data_;
};

void UsbRead_AddListener(void* self, Listener* listener) {
	Dispatcher_AddListener(USB_READ_EVENT_ID, listener);
}

UsbReadEvent* UsbReadEvent_New(unsigned char data) {
	UsbReadEvent* event = NEW(UsbReadEvent);
	event->data_ = data;
	return event;
}

void UsbReadEvent_Destroy(UsbReadEvent* self) {
	FREE(self);
}

unsigned char UsbReadEvent_GetData(UsbReadEvent* event) {
	return event->data_;
}
