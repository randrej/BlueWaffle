#include "AvrAdc.h"

/*******************************************************************************
 *  Public
 ******************************************************************************/
volatile uint8_t avrAdc_inputVector[3];
uint8_t avrAdc_inputVector_length = 3;

/*******************************************************************************
 *  Private
 ******************************************************************************/
uint8_t avrAdc_inputChannels[3] = {AVR_ADC_CHANNEL_CV, AVR_ADC_CHANNEL_FREQ,
                                   AVR_ADC_CHANNEL_BITS};
volatile uint8_t avrAdc_inputVectorIndex;

volatile uint8_t avrAdc_waiting;

/*******************************************************************************
 *  Implementation
 ******************************************************************************/
void avrAdc_init(void)
{
  sei();
  C_SETBIT(C_AVR_ADC_ENABLE);

  C_CLEARBIT(C_AVR_ADC_INTERRUPT_FLAG);
  C_SETBIT(C_AVR_ADC_INTERRUPT_ENABLE);

  C_SETBIT(C_AVR_ADC_AUTOTRIGGER);

  C_CLEARBIT(C_AVR_ADC_POWER_REDUCTION);

  // set prescaler to /128 for 125KHz ADC clock
  C_SETBIT(C_AVR_ADC_ADPS0);
  C_SETBIT(C_AVR_ADC_ADPS1);
  C_SETBIT(C_AVR_ADC_ADPS2);


  // set reference to AREF
  C_CLEARBIT(C_AVR_ADC_REFS1);
  C_CLEARBIT(C_AVR_ADC_REFS0);

  // align to msb: ADCH now contains 8 most significant bits of conversion
  C_SETBIT(C_AVR_ADC_MSB_ALIGN);

  // set input for ADC pins
  PC_SET_INPUT_TRISTATE(AVR_ADC_PIN_0);
  PC_SET_INPUT_TRISTATE(AVR_ADC_PIN_1);
  PC_SET_INPUT_TRISTATE(AVR_ADC_PIN_2);

  // block digital input for pins
  CLEARBIT(DIDR0, AVR_ADC_CHANNEL_CV);
  CLEARBIT(DIDR0, AVR_ADC_CHANNEL_FREQ);
  CLEARBIT(DIDR0, AVR_ADC_CHANNEL_BITS);

  // clear channels
  CLEARBITMASK(ADMUX, 0b111);
  // set first channel
  SETBITMASK(ADMUX, avrAdc_inputChannels[0]);
  C_SETBIT(C_AVR_ADC_STARTCONVERSION);
}


ISR(ADC_vect,
    ISR_NOBLOCK)  // non-blocking interrupt - we don't wanna block audio
{
  // ignore every second conversion because channel switching occurs only on
  // next non-started conversion
  if (avrAdc_waiting)
  {
    avrAdc_waiting = 0;
    return;
  }

  CLEARBITMASK(LAD_PINS_PORT, LAD_PINS_MASK);
  SETBIT(LAD_PINS_PORT, lad_flashPins[avrAdc_inputVectorIndex]);
  LAD_OUT_PORT = lad_ledsArray[avrAdc_inputVectorIndex];

  // read current channel
  avrAdc_inputVector[avrAdc_inputVectorIndex] = ADCH;

  // calculate next channel
  avrAdc_inputVectorIndex++;
  if (avrAdc_inputVectorIndex >= avrAdc_inputVector_length)
    avrAdc_inputVectorIndex = 0;

  // set next channel
  CLEARBITMASK(ADMUX, 0b111);
  SETBITMASK(ADMUX, avrAdc_inputChannels[avrAdc_inputVectorIndex]);

  // set the next conversion to be ignored
  avrAdc_waiting = 1;
}
