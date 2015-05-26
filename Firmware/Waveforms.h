#ifndef WAVEFORMS_H
#define WAVEFORMS_H

#include <avr/io.h>
#include <inttypes.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "AvrMacroLibrary.h"


/*******************************************************************************
 *  interface
 ******************************************************************************/
#define WAVES_READ_SAMPLE(N) pgm_read_byte(&waves_currentWaveformPointer[N])

extern uint8_t waves_currentWaveformNumber;
extern uint8_t* waves_currentWaveformPointer;
extern const uint8_t* waves_waveformArray[2];
extern uint8_t waves_waveformArray_length;

#endif