#ifndef AVR_AVR_ADC_H
#define AVR_AVR_ADC_H


#include "AvrMacroLibrary.h"
#include "LedsAndDisplay.h"
#include <avr/io.h>
#include <avr/interrupt.h>



/*******************************************************************************
 *  REGISTER COMBOS
 ******************************************************************************/
#define C_AVR_ADC_ENABLE ADCSRA, ADEN
#define C_AVR_ADC_INTERRUPT_FLAG ADCSRA, ADIF
#define C_AVR_ADC_INTERRUPT_ENABLE ADCSRA, ADIE

#define C_AVR_ADC_POWER_REDUCTION PRR0, PRADC

#define C_AVR_ADC_REFS0 ADMUX, REFS0
#define C_AVR_ADC_REFS1 ADMUX, REFS1

#define C_AVR_ADC_ADPS0 ADCSRA, ADPS0
#define C_AVR_ADC_ADPS1 ADCSRA, ADPS1
#define C_AVR_ADC_ADPS2 ADCSRA, ADPS2

#define C_AVR_ADC_MSB_ALIGN ADMUX, ADLAR

#define C_AVR_ADC_AUTOTRIGGER ADCSRA, ADATE
#define C_AVR_ADC_STARTCONVERSION ADCSRA, ADSC


/*******************************************************************************
 *  SETTINGS
 ******************************************************************************/

#define AVR_ADC_PIN_0 PORTA_P1
#define AVR_ADC_PIN_1 PORTA_P3
#define AVR_ADC_PIN_2 PORTA_P4

#define AVR_ADC_CHANNEL_CV 1
#define AVR_ADC_CHANNEL_FREQ 3
#define AVR_ADC_CHANNEL_BITS 4


/*******************************************************************************
 *  Interface
 ******************************************************************************/
void avrAdc_init(void);

#endif  // AVR_ADC_H