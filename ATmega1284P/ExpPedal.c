#include "ExpPedal.h"

static uint16_t VARIABLE_IS_NOT_USED lastValue;

void exp_init()
{
  adc_init();
  PC_SET_INPUT_TRISTATE(EXP_SW_PIN);
  adc_intHandlerSet(&exp_adcInterruptHandler);
}


void exp_inputPoll()
{
  adc_startConv();
  if (PC_CHECK(EXP_SW_PIN))
  {
    _midi_send_noteOn(_presets_current_expMidiChan,
                      _presets_current_expFootswitchMsg,
                      127);             // react immedeately (first trigger)
    _delay_ms(IO_SHORT_DEBOUNCE_TIME);  // debounce

    while (PC_CHECK(EXP_SW_PIN))
      ;  // wait for release
  }
}


void exp_adcInterruptHandler()
{
  uint16_t newVal = adc_getValue();
  newVal <<= 4;

  if (lastValue != newVal)
  {
    lastValue = newVal;

    uint8_t msb = lastValue >> 7;
    _midi_send_cc(
      _presets_current_expMidiChan, _presets_current_expCcChan, msb);

    volatile uint8_t* curr_cc14 = &_presets_current_CC14bit;

    if (*curr_cc14)
      if (_presets_current_expCcChan < 32)
      {
        uint8_t lsb = lastValue & 0b1111111;
        _midi_send_cc(
          _presets_current_expMidiChan, _presets_current_expCcChan + 32, lsb);
      }
  }
}