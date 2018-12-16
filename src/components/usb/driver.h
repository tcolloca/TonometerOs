/*
 * DRIVER FOR USB (USART0 / COM PROTOCOL)
 */
#ifndef COMPONENTS_USB_DRIVER_H_
#define COMPONENTS_USB_DRIVER_H_

/* Initialize driver. */
void Usb_Init();

/* Read data from the Usb port. */
unsigned char Usb_Read();

/* Write data to the Usb port. */
void Usb_Write(unsigned char data);

#endif  // COMPONENTS_USB_DRIVER_H_
