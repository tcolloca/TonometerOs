#include "event/listener.h"

#include "event/eventdef.h"
#include "lib/memory.h"
#include "util/util.h"

struct Listener {
	void* self_;
	void (*Handle_)(void*, Event*);
};

Listener* Listener_New(void* self, void (*Handle)(void*, Event*)) {
	Listener* listener = NEW(Listener);
	listener->Handle_ = Handle;
	listener->self_ = self;
	return listener;
}

void Listener_Handle(Listener* self, Event* event) {
	self->Handle_(self->self_, event);
}

void Listener_Destroy(Listener* self) {
	FREE(self);
}
