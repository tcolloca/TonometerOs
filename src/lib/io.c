#include "lib/io.h"

#include <stdio.h>

#include "components/internal/usb/usb.h"
#include "components/internal/usb/event.h"

#define READ_BUFFER_SIZE 10

static char read_buffer_[READ_BUFFER_SIZE + 1];
static int read_buffer_head_ = 0;
static int read_buffer_tail_ = 0;
static int read_buffer_count_ = 0;

static void Io_UsbReadListener(void* a_void, Event* event);

static int Usb_PutChar(char c, FILE *stream);

static int Usb_GetChar(FILE *stream);

static FILE usb_stdout = FDEV_SETUP_STREAM(Usb_PutChar, Usb_GetChar, _FDEV_SETUP_RW);

void Io_Init() {
	stdout = &usb_stdout;
	Listener* usb_read_listener = Listener_New(NULL, &Io_UsbReadListener);
	UsbRead_AddListener(NULL, usb_read_listener);
}

void Io_UsbReadListener(void* a_void, Event* event) {
	UsbReadEvent* usb_read_event = (UsbReadEvent*) event;
	unsigned char c = UsbReadEvent_GetData(usb_read_event);

	read_buffer_[read_buffer_head_] = c;

	if (++read_buffer_head_ > READ_BUFFER_SIZE) {
		read_buffer_head_ = 0;
	}

	if (++read_buffer_count_ > READ_BUFFER_SIZE) {
		read_buffer_count_ = READ_BUFFER_SIZE;
		Logger_AtError("Read buffer overflow.");
	}
}

static int Usb_PutChar(char c, FILE *stream) {
	if (c == '\n')
		Usb_Write('\r');
	Usb_Write(c);
	return 0;
}

static int Usb_GetChar(FILE *stream) {
	char c;
	while (read_buffer_count_ == 0)
		; /* wait for a new char */
	c = read_buffer_[read_buffer_tail_];

	if (++read_buffer_tail_ > READ_BUFFER_SIZE) {
		read_buffer_tail_ = 0;
	}

	if (read_buffer_count_ > 0) {
		read_buffer_count_--;
	}
	return c;
}

