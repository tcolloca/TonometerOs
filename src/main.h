/*
 * MICRO-CONTROLLER MAIN.
 */
#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>

/* Function to process every second. */
void Main_ProcessTicksSec(int secs);

/* Function to echo value read from usb plus one. */
void Main_EchoPlusOne(unsigned char data);

bool PrintError();

int main();

#endif  // MAIN_H_
