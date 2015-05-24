#include "LedDisplay.h"

LedDisplay::LedDisplay(uint8_t positionOfFirstDigit, BitShiftOut *outRegister) : _positionOfFirstDigit(positionOfFirstDigit), _outRegister(outRegister)
{
    //ctor
    LedDigit ledDigit1(_positionOfFirstDigit, _outRegister);
    LedDigit ledDigit2(_positionOfFirstDigit+1, _outRegister);

    _lsDigit = &ledDigit1;
    _msDigit = &ledDigit2;
}

void LedDisplay::displayDecWithoutShift(uint8_t number)
{
    if (number >= 0 && number<=99)
    {
        uint8_t LSDigit = number % 10;
        uint8_t MSDigit = (number/10) % 10;
        _lsDigit->showDecDigitWithoutShift(LSDigit);
        _msDigit->showDecDigitWithoutShift(MSDigit);
    }
}

void LedDisplay::displayHexWithoutShift(uint8_t number)
{
    if (number >= 0 && number<=0xff)
    {
        uint8_t LSDigit = number % 16;
        uint8_t MSDigit = (number/16) % 16;
        _lsDigit->showHexDigitWithoutShift(LSDigit);
        _msDigit->showHexDigitWithoutShift(MSDigit);
    }
}
