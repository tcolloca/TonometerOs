#include "components/usb/driver.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "components/usb/event.h"
#include "util/util.h"

void Usb_Init() {
	/* Configure bps for clock */

	UBRR0L = 7;  // bps: 115.2k with clock 14.7456MHz

	/* Set control register A */

	CLEAR(UCSR0A, U2X0);  // Normal Speed mode.
	CLEAR(UCSR0A, FE0);   // Set Frame Error bit to 0.

	/* Set control register B */

	SET(UCSR0B, RXCIE0);  // Set receive interrupt.
	SET(UCSR0B, RXEN0);   // Set receiver.
	SET(UCSR0B, TXEN0);   // Set transmitter.

	/* Set control register C */

	// Set data size to 8-bits.
	char data_size = 0;
	SET(data_size, UCSZ00);
	SET(data_size, UCSZ01);
	UCSR0C |= data_size;
}

unsigned char Usb_Read() {
	// Wait for data to be available.
	while (IS_CLEAR(UCSR0A, RXC0))
		;
	return UDR0;
}

void Usb_Write(unsigned char data) {
	// Wait for register to be clean.
	while (IS_CLEAR(UCSR0A, UDRE0))
		;
	UDR0 = data;
}

/* USART0 Receive Interrupt */
// TODO: Make it listener.
SIGNAL (USART0_RX_vect) {
	UsbReadEvent* event = UsbReadEvent_New(Usb_Read());
	Dispatcher_Dispatch(USB_READ_EVENT_ID, event);
	UsbReadEvent_Destroy(event);
}
