/*
 * LISTENER INTERFACE.
 */
#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

#include "event/eventdef.h"

typedef struct Listener Listener;

/* Create a new listener, delegating ownership.
 * Does not take ownership `self`. */
Listener* Listener_New(void* self, void (*Handle)(void*, Event*));

/* Handle event. */
void Listener_Handle(Listener* self, Event* event);

/* Destroy listener. */
void Listener_Destroy(Listener* self);

#endif  // EVENT_LISTENER_H_
