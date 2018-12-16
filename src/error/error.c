#include "error/error.h"

#include <stddef.h>
#include <stdbool.h>

static char* message_ = NULL;

void Error_Reset() {
	message_ = NULL;
}

bool Error_HasError() {
	return message_ != NULL;
}

char* Error_GetError() {
	return message_;
}

void Error_SetError(char* message) {
	message_ = message;
}
