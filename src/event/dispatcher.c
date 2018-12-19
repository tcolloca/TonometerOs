#include "event/dispatcher.h"

#include <stddef.h>
#include <stdio.h>

#include "event/eventdef.h"
#include "event/listener.h"
#include "lib/memory.h"
#include "logger/logger.h"
#include "util/util.h"

#define DISPATCHER_MAP_MAX_SIZE 16
#define LISTENERS_MAX_SIZE 16

typedef struct DispatcherEntry DispatcherEntry;

static Dispatcher* Dispatcher_New();

static Dispatcher* Dispatcher_GetInstance(EventId event_id);

static void DispatcherEntry_Destroy(DispatcherEntry* self);

static void Dispatcher_Destroy(Dispatcher* self);

struct DispatcherEntry {
	EventId event_id_;
	Dispatcher* dispatcher_;
};

struct Dispatcher {
	int listeners_size_;  // Defaults to 0
	Listener* listeners_[LISTENERS_MAX_SIZE];
};

static int dispatcher_map_size_ = 0;
static DispatcherEntry* dispatcher_map_[DISPATCHER_MAP_MAX_SIZE];

Dispatcher* Dispatcher_GetInstance(EventId event_id) {
	for (int i = 0; i < dispatcher_map_size_; i++) {
		if (dispatcher_map_[i]->event_id_ == event_id) {
			return dispatcher_map_[i]->dispatcher_;
		}
	}
	if (dispatcher_map_size_ < DISPATCHER_MAP_MAX_SIZE) {
		DispatcherEntry* new_entry = NEW(DispatcherEntry);
		new_entry->event_id_ = event_id;
		new_entry->dispatcher_ = Dispatcher_New();
		dispatcher_map_[dispatcher_map_size_++] = new_entry;
		return new_entry->dispatcher_;
	}
	Logger_AtError("Dispatcher map max size reached.");
	return NULL;
}

Dispatcher* Dispatcher_New() {
	Dispatcher* dispatcher = NEW(Dispatcher);
	dispatcher->listeners_size_ = 0;
	return dispatcher;
}

void Dispatcher_Dispatch(EventId event_id, Event* event) {
	Dispatcher* dispatcher = Dispatcher_GetInstance(event_id);
	for (int i = 0; i < dispatcher->listeners_size_; i++) {
		Listener_Handle(dispatcher->listeners_[i], event);
	}
}

void Dispatcher_AddListener(EventId event_id, Listener* listener) {
	Dispatcher* dispatcher = Dispatcher_GetInstance(event_id);
	printf("dispatcher listener size: %d", dispatcher->listeners_size_);
	if (dispatcher->listeners_size_ < LISTENERS_MAX_SIZE) {
		dispatcher->listeners_[dispatcher->listeners_size_++] = listener;
		return;
	}
	Logger_AtError("Listeners max size reached.");
}

void Dispatcher_DestroyAll() {
	for (int i = 0; i < dispatcher_map_size_; i++) {
		DispatcherEntry_Destroy(dispatcher_map_[i]);
	}
}

void DispatcherEntry_Destroy(DispatcherEntry* self) {
	Dispatcher_Destroy(self->dispatcher_);
	FREE(self);
}

void Dispatcher_Destroy(Dispatcher* self) {
	FREE(self);
}
