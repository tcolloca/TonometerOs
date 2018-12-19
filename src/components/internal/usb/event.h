/*
 * USB EVENT API.
 */
#ifndef COMPONENTS_INTERNAL_USB_EVENT_H_
#define COMPONENTS_INTERNAL_USB_EVENT_H_

#include "event/event.h"

typedef struct UsbReadEvent UsbReadEvent;

void UsbRead_AddListener(void* self, Listener* listener);

UsbReadEvent* UsbReadEvent_New(unsigned char data);

void UsbReadEvent_Destroy(UsbReadEvent* self);

unsigned char UsbReadEvent_GetData(UsbReadEvent* event);

#endif  // COMPONENTS_INTERNAL_USB_EVENT_H_
