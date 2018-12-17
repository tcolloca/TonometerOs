#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "components/adc/driver.h"
#include "components/air_pump/air_pump.h"
#include "components/ir_led/ir_led.h"
#include "components/led/driver.h"
#include "components/pwm/driver.h"
#include "components/timer/driver.h"
#include "components/timer/event.h"
#include "components/usb/driver.h"
#include "components/usb/event.h"
#include "error/error.h"
#include "event/event.h"
#include "lib/io.h"

#define DEBUG true

static int message_index = 0;
static char* message = NULL;

#define AIR_PUMP_PORT 'b'
#define AIR_PUMP_PIN   1

void Main_EchoPlusOne(unsigned char data) {
	Usb_Write(data);
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
		//Usb_Write(data);
		printf("read data: %d\n", data);
	}
}

void Main_UsbReadListener(void* a_void, Event* event) {
	UsbReadEvent* usb_read_event = (UsbReadEvent*) event;
	Main_EchoPlusOne(UsbReadEvent_GetData(usb_read_event));
}

bool PrintError() {
	if (message != NULL && message_index >= strlen(message)) {
		message_index = 0;
		message = NULL;
		Error_Reset();
	}
	if (message == NULL) {
		if (Error_HasError()) {
			message = Error_GetError();
		}
	}
	if (message != NULL) {
		Usb_Write(message[message_index++]);
		return true;
	}
	return false;
}

struct Test {
	char buffer;
};

typedef struct Test Test;


Test* GenStruct(){
	Test* ptr = (Test*)malloc(sizeof(Test));
	ptr->buffer = 't';

	return ptr;
}

int main() {

	Timer_Init();
	Led_Init();
//	IrLed_Init();
//	Pwm_Init();
	Usb_Init();
	Io_Init();
	Adc_Init();
	AirPump_Init(AIR_PUMP_PORT, AIR_PUMP_PIN);
//	Pwm_SetDutyCycle(0.95);

  // Global enable of interrupts.
	sei();

	Listener* timer_listener = Listener_New(NULL, &Main_TimerListener);
	Timer_AddListener(NULL, timer_listener);

	Listener* usb_read_listener = Listener_New(NULL, &Main_UsbReadListener);
	UsbRead_AddListener(NULL, usb_read_listener);

	Test* test = GenStruct();
	printf("%c \n",test->buffer);

	test->buffer = 'n';
	printf("%c \n",test->buffer);

	free(test);

	while (true) {
		if (DEBUG) {
		  PrintError();
		}
	}

	Listener_Destroy(timer_listener);
}

