#ifndef IOPROCESSOR_H
#define IOPROCESSOR_H

#include <avr/io.h>
#include <inttypes.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "AvrMacroLibrary.h"
#include "AvrAdc.h"
#include "Modes.h"


/*******************************************************************************
 *  port combos
 ******************************************************************************/

#define PC_IO_ENC_BUTTON	PORTB_P2
#define PC_IO_BITS_SWITCH PORTB_P1

#define PC_IO_ENC0 PORTB_P3
#define PC_IO_ENC1 PORTB_P4

#define IO_ENC_MASK 0b0011000
#define IO_ENC_SHIFT 3
#define IO_ENC_PIN PINB
#define IO_READ_ENCODER ((IO_ENC_PIN & IO_ENC_MASK) << IO_ENC_SHIFT)


/*******************************************************************************
 *  time constants
 ******************************************************************************/
#define IO_REPEAT_START_TIME 256
#define IO_REPEAT_MIN_TIME 32
#define IO_REPEAT_SHIFT_AMT 3

#define IO_SHORT_DEBOUNCE_TIME 20
#define IO_LONG_DEBOUNCE_TIME 250
#define IO_LONG_PRESS_TIME 1000


/*******************************************************************************
 *  interface
 ******************************************************************************/
void io_init();
void io_inputPoll();

#endif  // IOPROCESSOR_H
