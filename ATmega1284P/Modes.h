#ifndef MODES_H
#define MODES_H

#include <avr/io.h>
#include <inttypes.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "AvrMacroLibrary.h"
#include "LedsAndDisplay.h"
#include "spiAdc.h"

/*******************************************************************************
 *  Constants
 ******************************************************************************/
#define MODES_HP_SHIFT 4

/*******************************************************************************
 *  Structs
 ******************************************************************************/
typedef const struct __modeDefinition
{
  void (*init)(void);
  void (*handleChange)(void);

  void (*potFreqHandle)(void);
  void (*potBitsHandle)(void);
  void (*potCVHandle)(void);

  void (switchBitsHandle*)(void);

  void (*buttonModeShortpressHandle)(void);

  void (*encoderIncHandle)(void);
  void (*encoderDecHandle)(void);
} Mode;

/*******************************************************************************
 *  Interface
 ******************************************************************************/
void modes_nextMode();
void modes_prevMode();

extern Mode* modes_activeMode;
extern uint8_t modes_activeMode_index;
extern Mode modes_modeArray[];
extern uint8_t modes_modeArray_length;

#endif