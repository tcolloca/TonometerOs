/*
 * DRIVER FOR THE ANALOG-DIGITAL CONVERTER.
 */
#ifndef COMPONENTS_INTERNAL_ADC_ADC_H_
#define COMPONENTS_INTERNAL_ADC_ADC_H_

#include <stdint.h>
/* Initialize the driver. */
void Adc_Init();

/* Get ADC sample. */
uint16_t Adc_GetSample();

#endif  // COMPONENTS_INTERNAL_ADC_ADC_H_
