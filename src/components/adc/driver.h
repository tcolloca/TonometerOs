/*
 * DRIVER FOR THE ANALOG-DIGITAL CONVERTER.
 */
#ifndef COMPONENTS_ADC_DRIVER_H_
#define COMPONENTS_ADC_DRIVER_H_

#include <stdint.h>
/* Initialize the driver. */
void Adc_Init();

/* Get ADC sample. */
uint8_t Adc_GetSample();

#endif  // COMPONENTS_ADC_DRIVER_H_
