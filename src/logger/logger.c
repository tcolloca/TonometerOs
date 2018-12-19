#include "logger/logger.h"

#include <stdarg.h>
#include <stdio.h>

#define PRINT 	va_list args;        \
								va_start(args, fmt); \
								vprintf(fmt, args);  \
								printf("\n");

static Level level_ = INFO;

void Logger_SetLevel(Level level) {
	level_ = level;
}

void Logger_AtFinest(char* fmt, ...) {
	if (level_ > FINEST) {
		return;
	}
	printf("FINEST: ");
	PRINT
}

void Logger_AtFiner(char* fmt, ...) {
	if (level_ > FINER) {
		return;
	}
	printf("FINER: ");
	PRINT
}

void Logger_AtFine(char* fmt, ...) {
	if (level_ > FINE) {
		return;
	}
	printf("FINE: ");
	PRINT
}

void Logger_AtDebug(char* fmt, ...) {
	if (level_ > DEBUG) {
		return;
	}
	printf("DEBUG: ");
	PRINT
}

void Logger_AtInfo(char* fmt, ...) {
	if (level_ > INFO) {
		return;
	}
	printf("INFO: ");
	PRINT
}

void Logger_AtWarning(char* fmt, ...) {
	if (level_ > WARNING) {
		return;
	}
	printf("WARNING: ");
	PRINT
}

void Logger_AtError(char* fmt, ...) {
	if (level_ > ERROR) {
		return;
	}
	printf("ERROR: ");
	PRINT
}
