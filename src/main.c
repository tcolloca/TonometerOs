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
#include "config/config.h"
#include "lib/io.h"
#include "logger/logger.h"
#include "util/util.h"

static volatile bool measure = false;
static volatile bool measuring = false;
static volatile bool measure_eye_pressure = false;
static volatile bool measure_inc_tank_pressure = false;
static volatile bool measure_dec_tank_pressure = false;

static volatile uint16_t ir_led_max = 0;
static volatile uint32_t match_mpx_pressure = 0;

static int measurements_count = 0;

static void Measure();

static void Main_AirPump_TurnOn();

static void Main_AirPump_TurnOff();

static void Main_Valve_Open();

static void Main_Valve_Close();

void Main_HandleInput(unsigned char data) {
	Logger_AtInfo("Handling input: %c", data);
	switch (data) {
	case '1':
		Main_AirPump_TurnOn();
		break;
	case '2':
		Main_AirPump_TurnOff();
		break;
	case '3':
		Main_Valve_Open();
		break;
	case '4':
		Main_Valve_Close();
		break;
	case '9':
		measure = true;
		Measure();
		Logger_AtInfo("Eye pressure: UNKNOWN");
		break;
	}
}

static void Main_AirPump_TurnOn() {
	AirPump_TurnOn();
	measure_inc_tank_pressure = true;
}

static void Main_AirPump_TurnOff() {
	AirPump_TurnOff();
	measure_inc_tank_pressure = false;
	measure_dec_tank_pressure = true;
}

static void Main_Valve_Open() {
	Valve_Open();
	measure_dec_tank_pressure = false;
	measure_eye_pressure = true;
	ir_led_max = 0;
	match_mpx_pressure = 0;
}

static void Main_Valve_Close() {
	Valve_Close();
	measure_eye_pressure = false;
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
	uint16_t ir_receiver_data = IrReceiver_GetSample();
	Logger_AtInfo("IR Receiver: %d", ir_receiver_data);
	uint32_t mpx_sensor_pressure = MpxSensor_GetPressure();
	Logger_AtInfo("Output pressure (mmHg x 100): %lu", mpx_sensor_pressure);
	measuring = false;
	measure = false;
}

static void BlinkLed(uint32_t currSec) {
	if (currSec % 2 == 0) {
		Led_TurnOff();
	} else {
		Led_TurnOn();
	}
}

static void MeasureEyePressure() {
	if (measurements_count++ > MEASUREMENTS_COUNT) {
		measure_eye_pressure = false;
		measurements_count = 0;
		Logger_AtInfo("Ir Max: %d", ir_led_max);
		Logger_AtInfo("Mpx match pressure: %lu", match_mpx_pressure);
		Valve_Close();
	}
	uint32_t mpx_sensor_pressure = MpxSensor_GetPressure();
	Logger_AtInfo("Output pressure (mmHg x 100): %lu", mpx_sensor_pressure);

	uint16_t ir_receiver_data = IrReceiver_GetSample();
	Logger_AtInfo("IR Receiver: %d", ir_receiver_data);

	if (ir_receiver_data > ir_led_max) {
		ir_led_max = ir_receiver_data;
		match_mpx_pressure = mpx_sensor_pressure;
	}
}

static void MeasureIncTankPressure() {
	bmp280_measure();
	uint32_t bmp_pressure = bmp280_getpressure();
	Logger_AtInfo("Tank pressure (hPa x 100): %lu", bmp_pressure);
	if (bmp_pressure >= MAX_PRESSURE) {
		Main_AirPump_TurnOff();
	}
}

static void MeasureDecTankPressure() {
	bmp280_measure();
	uint32_t bmp_pressure = bmp280_getpressure();
	Logger_AtInfo("Tank pressure (hPa x 100): %lu", bmp_pressure);
	if (SEARCH_PRESSURE - DELTA_ERROR <= bmp_pressure &&
			bmp_pressure < SEARCH_PRESSURE + DELTA_ERROR) {
		Main_Valve_Open();
	} else if (bmp_pressure < SEARCH_PRESSURE - DELTA_ERROR) {
		Main_AirPump_TurnOn();
	}
}

int main() {
	Logger_SetLevel(LOGGER_LEVEL);

	Usb_Init();  // First one to init to be able to debug.
	Io_Init();

	Led_Init();
	Timer0_Init();
	Adc_Init();

	IrLed_Init(IR_LED_PORT, IR_LED_PIN);
	IrReceiver_Init(IR_RECEIVER_PORT, IR_RECEIVER_PIN);
	AirPump_Init(AIR_PUMP_PORT, AIR_PUMP_PIN);
	Valve_Init(VALVE_PORT, VALVE_PIN);
	MpxSensor_Init(MPX_SENSOR_PORT, MPX_SENSOR_PIN);

	bmp280_init();

// Global enable of interrupts.
	sei();

	Logger_AtInfo("*** TonometerOs v3.1 ***");

	uint32_t lastSec = 0, currSec = 0;
	uint64_t lastMillis = 0, currMillis = 0;
	uint64_t lastMicros = 0, currMicros = 0;
	while (true) {
		currMicros = Timer0_GetStartTimeInMicros();
		currMillis = currMicros / 1000;
		if (currMillis != lastMillis) {
			currSec = currMillis / 1000;
		}
		if (currSec != lastSec) {
			BlinkLed(currSec);
		}
		if (measure) {
			Measure();
		}
		if (measure_eye_pressure && currMicros / 100 != lastMicros / 100) {
//			MeasureEyePressure();
		}
		if (currMillis / 10 != lastMillis / 10) {
			if (measure_eye_pressure) {
				MeasureEyePressure();
			}
			if (measure_inc_tank_pressure) {
				MeasureIncTankPressure();
			}
			if (measure_dec_tank_pressure) {
				MeasureDecTankPressure();
			}
		}
		lastSec = currSec;
		lastMillis = currMillis;
		lastMicros = currMicros;
	}
}

