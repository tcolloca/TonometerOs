#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "components/external/air_pump/air_pump.h"
#include "components/external/ir_led/ir_led.h"
#include "components/internal/adc/adc.h"
#include "components/internal/led/led.h"
#include "components/internal/timer0/timer0.h"
#include "components/internal/usb/usb.h"
#include "components/internal/usb/event.h"
#include "config/config.h"
#include "event/event.h"
#include "lib/io.h"
#include "logger/logger.h"

static void Main_HandleInput(unsigned char data) {
	if (data == '1') {
		AirPump_TurnOn();
	} else if (data == '2') {
		AirPump_TurnOff();
	}
}

static void Main_UsbReadListener(void* a_void, Event* event) {
	UsbReadEvent* usb_read_event = (UsbReadEvent*) event;
	Main_HandleInput(UsbReadEvent_GetData(usb_read_event));
}

static uint32_t BlinkLed(uint32_t lastSec) {
	uint64_t currMillis = Timer0_GetStartTimeInMillis();
	uint32_t currSec = currMillis  / 1000;
	if (currSec != lastSec) {
		if (currSec % 2 == 0) {
			Led_TurnOff();
		} else {
			Led_TurnOn();
		}
		return currSec;
	}
	return lastSec;
}

int main() {
	Logger_SetLevel(LOGGER_LEVEL);

	Usb_Init(); // First one to init to be able to debug.
	Io_Init();

	Led_Init();
	Timer0_Init();
//	IrLed_Init();
	Adc_Init();
	AirPump_Init(AIR_PUMP_PORT, AIR_PUMP_PIN);

  // Global enable of interrupts.
	sei();

	Listener* usb_read_listener = Listener_New(NULL, &Main_UsbReadListener);
	UsbRead_AddListener(NULL, usb_read_listener);

	uint32_t lastSec = 0;
	while (true) {
		lastSec = BlinkLed(lastSec);
	}

	Listener_Destroy(usb_read_listener);
}

