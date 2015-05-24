#ifndef EXPPEDAL
#define EXPPEDAL

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "AvrMacroLibrary.h"
#include "SettingsAndDimensions.h"

#include "adc.h"
#include "MIDI.h"
#include "PresetManager.h"


#ifndef IO_SHORT_DEBOUNCE_TIME
#define IO_SHORT_DEBOUNCE_TIME 20
#endif

#define EXP_SW_PIN PORTA_P5

void exp_init();
void exp_inputPoll();

void exp_adcInterruptHandler();
#endif // EXPPEDAL
