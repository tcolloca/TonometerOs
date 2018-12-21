#include "main.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

#include "components/external/air_pump/air_pump.h"
#include "components/external/bmp280/bmp280.h"
#include "components/external/ir_receiver/ir_receiver.h"
#include "components/external/ir_led/ir_led.h"
#include "components/external/mpx_sensor/mpx_sensor.h"
#include "components/external/valve/valve.h"
#include "components/internal/adc/adc.h"
#include "components/internal/led/led.h"
#include "components/internal/timer0/timer0.h"
#include "components/internal/usb/usb.h"
#include "components/internal/usb/event.h"
#include "config/config.h"
#include "event/event.h"
#include "lib/io.h"
#include "logger/logger.h"
#include "util/util.h"

static volatile bool measure = false;
static volatile bool measuring = false;

static int freeRam();

static void Measure();

static void Main_HandleInput(unsigned char data) {
	Logger_AtInfo("Handling input: %c", data);
	switch (data) {
	case '1':
		AirPump_TurnOn();
		break;
	case '2':
		AirPump_TurnOff();
		break;
	case '3':
		Valve_Open();
		break;
	case '4':
		Valve_Close();
		break;
	case '5':
		Logger_AtInfo("\n[memCheck] %d", freeRam());
		break;
	case '9':
		measure = true;
		Measure();
		Logger_AtInfo("Eye pressure: UNKNOWN");
		break;
	}
}

static void Measure() {
	Logger_AtInfo("Measuring...");
	if (measuring) {
		return;
	}
	measuring = true;
	bmp280_measure();
	uint32_t bmp_pressure = bmp280_getpressure();
	Logger_AtInfo("Tank pressure (hPa x 100): %lu", bmp_pressure);
//	uint16_t ir_receiver_data = IrReceiver_GetSample();
//	Logger_AtInfo("IR Receiver: %d", ir_receiver_data);
//	uint32_t mpx_sensor_pressure = MpxSensor_GetPressure();
//	Logger_AtInfo("Output pressure (mmHg x 100): %lu", mpx_sensor_pressure);
	measuring = false;
	measure = false;
}

static void Main_UsbReadListener(void* a_void, Event* event) {
	UsbReadEvent* usb_read_event = (UsbReadEvent*) event;
	Main_HandleInput(UsbReadEvent_GetData(usb_read_event));
}

static uint32_t BlinkLed(uint32_t lastSec) {
	uint64_t currMillis = Timer0_GetStartTimeInMillis();
	uint32_t currSec = currMillis / 1000;
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

static int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	Logger_AtInfo("mem: %d, %d", __heap_start, __brkval);
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

int main() {
	Logger_SetLevel(LOGGER_LEVEL);
//
	Usb_Init();  // First one to init to be able to debug.
	Io_Init();

	Led_Init();
	Timer0_Init();
	Adc_Init();

	Logger_AtInfo("Mem check:  %d", freeRam());
	IrLed_Init(IR_LED_PORT, IR_LED_PIN);
	IrReceiver_Init(IR_RECEIVER_PORT, IR_RECEIVER_PIN);
	AirPump_Init(AIR_PUMP_PORT, AIR_PUMP_PIN);
	Valve_Init(VALVE_PORT, VALVE_PIN);
	MpxSensor_Init(MPX_SENSOR_PORT, MPX_SENSOR_PIN);

	bmp280_init();

	// Global enable of interrupts.
	sei();


	Logger_AtInfo("*** TonometerOs v3.1 ***");
	Listener* usb_read_listener = Listener_New(NULL, &Main_UsbReadListener);
	UsbRead_AddListener(NULL, usb_read_listener);

	uint32_t lastSec = 0;
	while (true) {
		lastSec = BlinkLed(lastSec);
		if (measure) {
			Measure();
		}
	}

	Listener_Destroy(usb_read_listener);
}

