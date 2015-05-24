#ifndef LEDDISPLAY_H
#define LEDDISPLAY_H

#include <LedDigit.h>
#include <BitShiftOut.h>

#define NUMBER_OF_DIGITS 2

class LedDisplay
{
    public:
        LedDisplay(uint8_t _positionOfFirstDigit, BitShiftOut *_outRegister);
        void displayDecWithoutShift(uint8_t number);
        void displayHexWithoutShift(uint8_t number);

    protected:
    private:
        uint8_t _positionOfFirstDigit;
        BitShiftOut *_outRegister;
        LedDigit *_lsDigit;
        LedDigit *_msDigit;

};

#endif // LEDDISPLAY_H
