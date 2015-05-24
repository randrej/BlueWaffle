#ifndef MILLISECONDS_H
#define MILLISECONDS_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "AvrMacroLibrary.h"

#define TIMER1_PRESCALE 8
#define TIMER1_RESET_COUNT ((F_CPU / 1000) / TIMER1_PRESCALE)


void _milliseconds_init();
unsigned long _milliseconds();


#endif // MILLISECONDS_H


