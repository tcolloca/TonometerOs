/*
 * DRIVER FOR THE IR RECEIVER.
 */
#ifndef COMPONENTS_EXTERNAL_IR_RECEIVER_IR_RECEIVER_H_
#define COMPONENTS_EXTERNAL_IR_RECEIVER_IR_RECEIVER_H_

#include <stdint.h>

/* Initialize the driver. */
void IrReceiver_Init(char port, uint8_t pin_number);

/* Gets a sample from the IR Receiver. */
uint16_t IrReceiver_GetSample();

#endif  // COMPONENTS_EXTERNAL_IR_RECEIVER_IR_RECEIVER_H_
