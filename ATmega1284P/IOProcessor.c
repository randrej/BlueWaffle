#include "IOProcessor.h"

/*******************************************************************************
 *  public
 ******************************************************************************/
volatile uint8_t io_curr_pots[3];
volatile uint8_t io_curr_bits_sw;


/*******************************************************************************
 *  private
 ******************************************************************************/
const uint8_t io_greyToState[] PROGMEM = {0, 1, 3, 2};
const uint8_t io_nextState[] PROGMEM = {1, 2, 3, 0};
const uint8_t io_prevState[] PROGMEM = {3, 0, 1, 2};

volatile uint8_t io_curr_enc_state;
volatile uint8_t io_dbc_enc;

/*******************************************************************************
 *  implementation
 ******************************************************************************/

void io_init()
{
  // input states
  PC_SET_INPUT_TRISTATE(PC_IO_ENC_BUTTON);
  PC_SET_INPUT_TRISTATE(PC_IO_BITS_SWITCH);
  PC_SET_INPUT_TRISTATE(PC_IO_ENC0);
  PC_SET_INPUT_TRISTATE(PC_IO_ENC1);

  // read initial encoder state
  uint8_t encInp = IO_READ_ENCODER;
  io_curr_enc_state = pgm_read_byte(&io_greyToState[encInp]);

  // read initial button statuses
  io_curr_bits_sw = PC_CHECK(PC_IO_BITS_SWITCH);

  // read initial pot values
  for (int i = 0; i < avrAdc_inputVector_length; ++i)
  {
    io_curr_pots[i] = avrAdc_inputVector[i];
  }

  // TODO: finish initialization of inputs
}


void io_inputPoll()
{
  // encoder button handling
  if (PC_CHECK(PC_IO_ENC_BUTTON))
  {
    // react immedeately (first trigger)
    modes_activeMode->buttonModeShortpressHandle();
    _delay_ms(IO_SHORT_DEBOUNCE_TIME);  // debounce

    while (PC_CHECK(PC_IO_ENC_BUTTON))
      ;                                 // wait for release
    _delay_ms(IO_SHORT_DEBOUNCE_TIME);  // debounce
  }

  // bits switch handling
  if (PC_CHECK(PC_IO_BITS_SWITCH) != io_curr_bits_sw)
  {
    // react immedeately
    io_curr_bits_sw = PC_CHECK(PC_IO_BITS_SWITCH);
    modes_activeMode->switchBitsHandle();
    _delay_ms(IO_SHORT_DEBOUNCE_TIME);  // debounce
  }

  // pot handling
  if (avrAdc_inputVector[AVR_ADC_CHANNEL_CV] !=
      io_curr_pots[AVR_ADC_CHANNEL_CV])
  {
    io_curr_pots[AVR_ADC_CHANNEL_CV] = avrAdc_inputVector[AVR_ADC_CHANNEL_CV];
    modes_activeMode->potCVHandle();
  }
  if (avrAdc_inputVector[AVR_ADC_CHANNEL_FREQ] !=
      io_curr_pots[AVR_ADC_CHANNEL_FREQ])
  {
    io_curr_pots[AVR_ADC_CHANNEL_FREQ] =
      avrAdc_inputVector[AVR_ADC_CHANNEL_FREQ];
    modes_activeMode->potFreqHandle();
  }
  if (avrAdc_inputVector[AVR_ADC_CHANNEL_BITS] !=
      io_curr_pots[AVR_ADC_CHANNEL_BITS])
  {
    io_curr_pots[AVR_ADC_CHANNEL_BITS] =
      avrAdc_inputVector[AVR_ADC_CHANNEL_BITS];
    modes_activeMode->potBitsHandle();
  }
}