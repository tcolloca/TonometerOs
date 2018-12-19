/*
 * EVENT DEF.
 */
#ifndef EVENT_EVENTDEF_H_
#define EVENT_EVENTDEF_H_

typedef enum EventId {USB_READ_EVENT_ID = 1, ADC_READ_EVENT_ID = 2,
											UNSET_EVENT_ID = 0} EventId;

typedef void Event;

#endif  // EVENT_EVENTDEF_H_
