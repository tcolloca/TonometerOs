#include "components/gpio/gpio.h"

#include <avr/io.h>

#include <stdbool.h>
#include <stdint.h>

#include "util/util.h"

#define REG_SWITCH_SET(reg, port, mask) \
		switch (port) { \
		case 'a': \
		case 'A': \
			SET_MASK(CAT(reg, A), mask); \
			break; \
		case 'b': \
		case 'B': \
			SET_MASK(CAT(reg, B), mask); \
			break; \
		case 'c': \
		case 'C': \
			SET_MASK(CAT(reg, C), mask); \
			break; \
		case 'd': \
		case 'D': \
			SET_MASK(CAT(reg, D), mask); \
			break; \
		} \

#define REG_SWITCH_CLEAR(reg, port, mask)  \
		switch (port) { \
		case 'a': \
		case 'A': \
			CLEAR_MASK(CAT(reg, A), mask); \
			break; \
		case 'b': \
		case 'B': \
			CLEAR_MASK(CAT(reg, B), mask); \
			break; \
		case 'c': \
		case 'C': \
			CLEAR_MASK(CAT(reg, C), mask); \
			break; \
		case 'd': \
		case 'D': \
			CLEAR_MASK(CAT(reg, D), mask); \
			break; \
		} \

#define REG_SWITCH_N_GET(reg, port, mask)  \
		switch (port) { \
		case 'a': \
		case 'A': \
			return ~CAT(reg, A) & mask; \
		case 'b': \
		case 'B': \
			return ~CAT(reg, B) & mask; \
		case 'c': \
		case 'C': \
			return ~CAT(reg, C) & mask; \
		case 'd': \
		case 'D': \
			return ~CAT(reg, D) & mask; \
		} \


void Gpio_InitPin(char port, uint8_t pin_number, bool output) {
	Gpio_InitWithMask(port, (1 << pin_number), output);
}

void Gpio_InitAll(char port, bool output) {
	Gpio_InitWithMask(port, 0xFF, output);
}

void Gpio_InitWithMask(char port, uint8_t mask,
		bool output) {
	if (output) {
		REG_SWITCH_SET(DDR, port, mask);
	} else {
		REG_SWITCH_CLEAR(DDR, port, mask);
		REG_SWITCH_SET(PORT, port, mask);
	}
}

void Gpio_SetPin(char port, uint8_t pin_number) {
	Gpio_SetMask(port, (1 << pin_number));
}

void Gpio_SetMask(char port, uint8_t mask) {
	REG_SWITCH_SET(PORT, port, mask);
}

void Gpio_ClearPin(char port, uint8_t pin_number) {
	Gpio_ClearMask(port, (1 << pin_number));
}

void Gpio_ClearMask(char port, uint8_t mask) {
	REG_SWITCH_CLEAR(PORT, port, mask);
}

bool Gpio_ReadPin(char port, uint8_t pin_number) {
	return Gpio_ReadWithMask(port, (1 << pin_number)) >> pin_number;
}

uint8_t Gpio_ReadAll(char port) {
	return Gpio_ReadWithMask(port, 0xFF);
}

uint8_t Gpio_ReadWithMask(char port, uint8_t mask) {
	if (port == PORTA) {
		return ~PINA & mask;
	} else if (port == PORTB) {
		return ~PINB & mask;
	} else if (port == PORTC) {
		return ~PINC & mask;
	} else if (port == PORTD) {
		return ~PIND & mask;
	} else {
		// TODO: Error.
		return 0;
	}
}
