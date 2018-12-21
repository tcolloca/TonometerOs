#ifndef LIB_IO_H_
#define LIB_IO_H_

#include <stddef.h>

/* Initialize the IO for use of stdio.h functions. */
void Io_Init();

void Io_UsbReadListener(unsigned char c);

#endif  // LIB_IO_H_
