/*
 * ERROR HANDLING FUNCTIONS.
 */
#ifndef ERROR_ERROR_H_
#define ERROR_ERROR_H_

#include <stdbool.h>

/* Reset the current error. */
void Error_Reset();

/* Returns whether there's a current error. */
bool Error_HasError();

/* Returns the current error. */
char* Error_GetError();

/* Set an error. */
void Error_SetError(char* message);

#endif  // ERROR_ERROR_H_
