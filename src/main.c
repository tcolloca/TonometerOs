#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <components/internal/pwm/pwm.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "components/external/air_pump/air_pump.h"
#include "components/external/ir_led/ir_led.h"
#include "components/internal/adc/adc.h"
#include "components/internal/led/led.h"
#include "components/internal/timer0/event.h"
#include "components/internal/timer0/timer0.h"
#include "components/internal/usb/usb.h"
#include "components/internal/usb/event.h"
#include "config/config.h"
#include "event/event.h"
#include "lib/io.h"
#include "logger/logger.h"

void Main_HandleInput(unsigned char data) {
	if (data == '1') {
		AirPump_TurnOn();
	} else if (data == '2') {
		AirPump_TurnOff();
	}
}

void Main_ProcessTicksSec(int secs) {
	if (secs % 2 == 0) {
		Usb_Write('(');
		Led_TurnOff();
	} else {
		Usb_Write(')');
		Led_TurnOn();
	}
}

void Main_TimerListener(void* a_void, Event* event) {
	TimerEvent* timer_event = (TimerEvent*) event;
	if (TimerEvent_GetTicks(timer_event) % 1000 == 0) {
		Main_ProcessTicksSec(TimerEvent_GetTicks(timer_event) / 1000);
		uint8_t data = Adc_GetSample();
		Logger_AtInfo("Data read: %d\n", data);
	}
}

void Main_UsbReadListener(void* a_void, Event* event) {
	UsbReadEvent* usb_read_event = (UsbReadEvent*) event;
	Main_HandleInput(UsbReadEvent_GetData(usb_read_event));
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

	Listener* timer_listener = Listener_New(NULL, &Main_TimerListener);
	Timer_AddListener(NULL, timer_listener);

	Listener* usb_read_listener = Listener_New(NULL, &Main_UsbReadListener);
	UsbRead_AddListener(NULL, usb_read_listener);

	while (true) {
		;
	}

	Listener_Destroy(timer_listener);
	Listener_Destroy(usb_read_listener);
}

