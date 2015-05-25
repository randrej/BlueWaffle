#ifndef LAD_H
#define LAD_H

#include "AvrMacroLibrary.h"
#include <avr/pgmspace.h>
#include <avr/io.h>


/*******************************************************************************
 *  positions
 ******************************************************************************/
#define LAD_DISPLAY_LSD 7
#define LAD_DISPLAY_MSD 6
#define LAD_LEDS 5

#define LAD_OUT_PORT PORTD
#define LAD_OUT_DIR DDRD

#define LAD_PINS_MASK 0b11100000
#define LAD_PINS_PORT PORTA
#define LAD_PINS_DIR DDRA

#define LAD_INDEX_MSD 1
#define LAD_INDEX_LSD 2
#define LAD_INDEX_LEDS 0

#define LAD_LEDS_ACCESS lad_ledsArray[LAD_INDEX_LEDS]

/*******************************************************************************
 *  interface
 ******************************************************************************/
void lad_init();

void lad_display_dec(uint8_t number);
void lad_display_hex(uint8_t number);
extern volatile uint8_t lad_ledsArray[];
extern uint8_t lad_flashPins[];

#endif  // PROGMEMTEXT_H
