#include "lib/io.h"

#include <stdio.h>

#include "components/internal/usb/usb.h"
#include "logger/logger.h"
#include "main.h"

#define READ_BUFFER_SIZE 1

static char read_buffer_[READ_BUFFER_SIZE + 1];
static int read_buffer_tail_ = 0;
static int read_buffer_count_ = 0;

static int Usb_PutChar(char c, FILE *stream);

static int Usb_GetChar(FILE *stream);

static FILE usb_stdout = FDEV_SETUP_STREAM(Usb_PutChar, Usb_GetChar, _FDEV_SETUP_RW);

void Io_Init() {
	stdout = &usb_stdout;

	printf("\n\n\n"); // Add distance from garbage.
	Logger_AtDebug("Initialized I/O via Uart (Usb).");
}

void Io_UsbReadListener(unsigned char c) {
	Main_HandleInput(c);
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

//	printf("Pulling char from buffer: %c", c);

	if (++read_buffer_tail_ > READ_BUFFER_SIZE) {
		read_buffer_tail_ = 0;
	}

	if (read_buffer_count_ > 0) {
		read_buffer_count_--;
	}
	return c;
}

