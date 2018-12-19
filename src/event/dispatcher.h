/*
 * DISPATCHER INTERFACE.
 */
#ifndef EVENT_DISPATCHER_H_
#define EVENT_DISPATCHER_H_

#include "event/eventdef.h"
#include "event/listener.h"

typedef struct Dispatcher Dispatcher;

/* Dispatch event to all listener. */
void Dispatcher_Dispatch(EventId event_id, Event* event);

/* Add listener to corresponding dispatcher.
 * Does not take ownership of listeners. */
void Dispatcher_AddListener(EventId event_id, Listener* listener);

/* Destroy all dispatchers. */
void Dispatcher_DestroyAll();

#endif  // EVENT_DISPATCHER_H_
