#ifndef LEDDIGIT_H_INCLUDED
#define LEDDIGIT_H_INCLUDED

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <BitShiftOut.h>

class LedDigit
{
private:
    uint8_t _positionOfLedDigit;
    BitShiftOut *_outRegister;

    static prog_uchar _ledDecDigits[11];
    static prog_uchar _ledHexDigits[16];

public:
    LedDigit(uint8_t positionOfLedDigit, BitShiftOut *outRegister);
    void showDecDigit(int8_t digit);
    void showDecDigitWithoutShift(int8_t digit);
    void showHexDigit(int8_t digit);
    void showHexDigitWithoutShift(int8_t digit);


};

#endif // LEDDIGIT_H_INCLUDED
