/*
 * ADC EVENT API.
 */
#ifndef COMPONENTS_ADC_EVENT_H_
#define COMPONENTS_ADC_EVENT_H_

#include "event/event.h"

typedef struct AdcReadEvent AdcReadEvent;

void AdcRead_AddListener(void* self, Listener* listener);

AdcReadEvent* AdcReadEvent_New(int data);

void AdcReadEvent_Destroy(AdcReadEvent* self);

int AdcReadEvent_GetData(AdcReadEvent* event);

#endif  // COMPONENTS_ADC_EVENT_H_
