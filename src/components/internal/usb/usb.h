/*
 * DRIVER FOR USB (USART0 / COM PROTOCOL)
 */
#ifndef COMPONENTS_INTERNAL_USB_USB_H_
#define COMPONENTS_INTERNAL_USB_USB_H_

/* Initialize driver. */
void Usb_Init();

/* Read data from the Usb port. */
unsigned char Usb_Read();

/* Write data to the Usb port. */
void Usb_Write(unsigned char data);

#endif  // COMPONENTS_INTERNAL_USB_USB_H_
