#include <LedDigit.h>

// MSBfirst
prog_uchar LedDigit::_ledDecDigits[11] PROGMEM = {
  0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110,
  0b10111110, 0b11100000, 0b11111110, 0b11110110, 0b10011111};
// LSBfirst:

prog_uchar LedDigit::_ledHexDigits[16] PROGMEM = {
  0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110,
  0b10111110, 0b11100000, 0b11111110, 0b11110110, 0b11101110, 0b111110,
  0b10011100, 0b1111010,  0b10011110, 0b10001110};


LedDigit::LedDigit(uint8_t positionOfLedDigit, BitShiftOut* outRegister)
  : _positionOfLedDigit(positionOfLedDigit), _outRegister(outRegister)
{
}

void LedDigit::showDecDigitWithoutShift(int8_t digit)
{
  uint8_t segments = pgm_read_byte(_ledDecDigits);
  if (digit >= 0 && digit <= 9)
  {
    segments = pgm_read_byte(_ledDecDigits + digit);
  }
  _outRegister->setRegisterWithNumber(segments, _positionOfLedDigit);
}

void LedDigit::showDecDigit(int8_t digit)
{
  showDecDigitWithoutShift(digit);
  _outRegister->shift();
}

void LedDigit::showHexDigit(int8_t digit)
{
  showHexDigitWithoutShift(digit);
  _outRegister->shift();
}

void LedDigit::showHexDigitWithoutShift(int8_t digit)
{
  uint8_t segments = pgm_read_byte(_ledHexDigits);
  if (digit >= 0 && digit <= 9)
  {
    segments = pgm_read_byte(_ledHexDigits + digit);
  }
  _outRegister->setRegisterWithNumber(segments, _positionOfLedDigit);
}
