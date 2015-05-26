#ifndef AVRMACROLIBRARY_H_INCLUDED
#define AVRMACROLIBRARY_H_INCLUDED

/*******************************************************************************
 *  ANDREJ'S AVR MACRO LIBRARY, WRITTEN BY ANDREJ RADOVIC (r.andrej@gmail.com)
 *  VISIT andrejsdiystuff.wordpress.com FOR MORE EMBEDDED AND GUITAR-RELATED

 This library is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


/*******************************************************************************
 *  REQS FOR PCS AND VARIABLE / BIT COMBOS (don't use)
 ******************************************************************************/
#include <avr/io.h>
#define EXPAND_COMBO(COMBO) COMBO


/*******************************************************************************
 *  ARITHMETIC OPERATIONS
 ******************************************************************************/
#define MODULO(x, y) ((x) - (((x) / (y)) * (y)))

/*******************************************************************************
 *  BITWISE OPERATION MACROS
 ******************************************************************************/
#define BIT(x) (0x01 << x)

#define SETBIT(ADDRESS, BITNUM) (ADDRESS |= (1 << BITNUM))
#define CLEARBIT(ADDRESS, BITNUM) ((ADDRESS) &= ~BIT(BITNUM))
#define FLIPBIT(ADDRESS, BITNUM) ((ADDRESS) ^= BIT(BITNUM))
#define CHECKBIT(ADDRESS, BITNUM) ((ADDRESS)&BIT(BITNUM))
#define WRITEBIT(COND, ADDRESS, BITNUM)                                        \
  if (COND)                                                                    \
  {                                                                            \
    SETBIT(ADDRESS, BITNUM);                                                   \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    CLEARBIT(ADDRESS, BITNUM);                                                 \
  }

#define SETBITMASK(x, y) ((x) |= (y))
#define CLEARBITMASK(x, y) ((x) &= ~(y))
#define FLIPBITMASK(x, y) ((x) ^= (y))
#define CHECKBITMASK(x, y) ((x) & (y))

/*******************************************************************************
 *  VARIABLE / BIT COMBOS
 *******************************************************************************
For easier manipulations of specific bits of variables/registers. Useful when
manipulating various AVR setting registers. Usage:

#define C_ADEN ADCSRA, ADEN
C_SETBIT(C_ADEN); // sets the adc enable bit on ADCSRA
          -> ADCSRA |= (1 << ADEN);
*******************************************************************************/
// don't use these, these are just for further expansion
#define _VARFROMCOMB(var, bit) var
#define _BITFROMCOMB(var, bit) bit

// by all means, use these
#define C_BIT(COMBO) EXPAND_COMBO(_BITFROMCOMB(COMBO))
#define C_VAR(COMBO) EXPAND_COMBO(_VARFROMCOMB(COMBO))

#define C_SETBIT(COMBO) SETBIT(_VARFROMCOMB(COMBO), _BITFROMCOMB(COMBO))
#define C_CLEARBIT(COMBO) CLEARBIT(_VARFROMCOMB(COMBO), _BITFROMCOMB(COMBO))
#define C_FLIPBIT(COMBO) FLIPBIT(_VARFROMCOMB(COMBO), _BITFROMCOMB(COMBO))
#define C_CHECKBIT(COMBO) CHECKBIT(_VARFROMCOMB(COMBO), _BITFROMCOMB(COMBO))


/*******************************************************************************
 *  MACRO/NAME CONCATENATION
 *******************************************************************************
For concatenating various macro-defined and argument-based names. Usage:

#define MIDI_SERIAL_PREFIX usart0_
#define MIDI_SERIAL_CALL(fun) EVALUATOR(MIDI_SERIAL_PREFIX,fun)

MIDI_SERIAL_CALL(init)();
                    ->  usart0_init();
*******************************************************************************/
#define PASTER(x, y) x##y
#define EVALUATOR(x, y) PASTER(x, y)


/*******************************************************************************
 *  PORT COMBOS
 *******************************************************************************
usage:
define your ports with macros to PORTX_PY
example:
#define CLOCK_PORT PORTD_P6

* set pin state:
PC_SET_INPUT_TRISTATE(COMBO)
PC_SET_INPUT_PULLUP(COMBO)
PC_SET_OUTPUT_PULLUP(COMBO)
example:
PC_SET_OUTPUT_PULLUP(CLOCK_PORT);

* alter/read pin data with:
PC_SET(COMBO)
PC_CLEAR(COMBO)
PC_FLIP(COMBO)
PC_CHECK(COMBO)
PC_WRITE(COND, COMBO)
example:
PC_SET(CLOCK_PORT)

* you can also get individual data from combos:
PC_BIT(CLOCK_PORT) returns PIND6
PC_PORT(CLOCK_PORT) returns PORTD
PC_PIN(CLOCK_PORT) returns PIND
PC_DDR(CLOCK_PORT) returns DDDRD
*******************************************************************************/
// don't use these, these are just for further expansion
#define _PC_BIT(PIN_NUM, PORT, PIN, DDR) PIN_NUM
#define _PC_PORT(PIN_NUM, PORT, PIN, DDR) PORT
#define _PC_PIN(PIN_NUM, PORT, PIN, DDR) PIN
#define _PC_DDR(PIN_NUM, PORT, PIN, DDR) DDR

// by all means, use these
#define PC_BIT(COMBO) EXPAND_COMBO(_PC_BIT(COMBO))
#define PC_PORT(COMBO) EXPAND_COMBO(_PC_PORT(COMBO))
#define PC_PIN(COMBO) EXPAND_COMBO(_PC_PIN(COMBO))
#define PC_DDR(COMBO) EXPAND_COMBO(_PC_DDR(COMBO))

#define PC_SET_INPUT_TRISTATE(COMBO)                                           \
  CLEARBIT(_PC_DDR(COMBO), _PC_BIT(COMBO));                                    \
  CLEARBIT(_PC_PORT(COMBO), _PC_BIT(COMBO))
#define PC_SET_INPUT_PULLUP(COMBO)                                             \
  CLEARBIT(_PC_DDR(COMBO), _PC_BIT(COMBO));                                    \
  SETBIT(_PC_PORT(COMBO), _PC_BIT(COMBO))
#define PC_SET_OUTPUT(COMBO) SETBIT(_PC_DDR(COMBO), _PC_BIT(COMBO))
#define PC_SET_INPUT(COMBO) CLEARBIT(_PC_DDR(COMBO), _PC_BIT(COMBO))

#define PC_SET(COMBO) SETBIT(_PC_PORT(COMBO), _PC_BIT(COMBO))
#define PC_CLEAR(COMBO) CLEARBIT(_PC_PORT(COMBO), _PC_BIT(COMBO))
#define PC_FLIP(COMBO) FLIPBIT(_PC_PORT(COMBO), _PC_BIT(COMBO))
#define PC_CHECK(COMBO) CHECKBIT(_PC_PIN(COMBO), _PC_BIT(COMBO))
#define PC_READ(COMBO)                                                         \
  (CHECKBIT(_PC_PIN(COMBO), _PC_BIT(COMBO))) >> _PC_BIT(COMBO)
#define PC_WRITE(COND, COMBO) WRITEBIT(COND, _PC_PORT(COMBO), _PC_BIT(COMBO))

/*******************************************************************************
 *  GCC variable is not used bullshit
 *******************************************************************************
Use this macro to get rid of GCC's false 'variable is not used'. It's
compiler-portable, though. Usage:

static uint8_t VARIABLE_IS_NOT_USED localVar;  //localVar no longer reported as
                                               //unused
*******************************************************************************/
#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

/*******************************************************************************
 *  PREDEFINED PORT COMBOS
 ******************************************************************************/
#ifdef PORTA
#define __PORTA_P0 PINA0, PORTA, PINA, DDRA
#define PORTA_P0 __PORTA_P0
#define __PORTA_P1 PINA1, PORTA, PINA, DDRA
#define PORTA_P1 __PORTA_P1
#define __PORTA_P2 PINA2, PORTA, PINA, DDRA
#define PORTA_P2 __PORTA_P2
#define __PORTA_P3 PINA3, PORTA, PINA, DDRA
#define PORTA_P3 __PORTA_P3
#define __PORTA_P4 PINA4, PORTA, PINA, DDRA
#define PORTA_P4 __PORTA_P4
#define __PORTA_P5 PINA5, PORTA, PINA, DDRA
#define PORTA_P5 __PORTA_P5
#define __PORTA_P6 PINA6, PORTA, PINA, DDRA
#define PORTA_P6 __PORTA_P6
#define __PORTA_P7 PINA7, PORTA, PINA, DDRA
#define PORTA_P7 __PORTA_P7
#endif

#ifdef PORTB
#define __PORTB_P0 PINB0, PORTB, PINB, DDRB
#define PORTB_P0 __PORTB_P0
#define __PORTB_P1 PINB1, PORTB, PINB, DDRB
#define PORTB_P1 __PORTB_P1
#define __PORTB_P2 PINB2, PORTB, PINB, DDRB
#define PORTB_P2 __PORTB_P2
#define __PORTB_P3 PINB3, PORTB, PINB, DDRB
#define PORTB_P3 __PORTB_P3
#define __PORTB_P4 PINB4, PORTB, PINB, DDRB
#define PORTB_P4 __PORTB_P4
#define __PORTB_P5 PINB5, PORTB, PINB, DDRB
#define PORTB_P5 __PORTB_P5
#define __PORTB_P6 PINB6, PORTB, PINB, DDRB
#define PORTB_P6 __PORTB_P6
#define __PORTB_P7 PINB7, PORTB, PINB, DDRB
#define PORTB_P7 __PORTB_P7
#endif

#ifdef PORTC
#define __PORTC_P0 PINC0, PORTC, PINC, DDRC
#define PORTC_P0 __PORTC_P0
#define __PORTC_P1 PINC1, PORTC, PINC, DDRC
#define PORTC_P1 __PORTC_P1
#define __PORTC_P2 PINC2, PORTC, PINC, DDRC
#define PORTC_P2 __PORTC_P2
#define __PORTC_P3 PINC3, PORTC, PINC, DDRC
#define PORTC_P3 __PORTC_P3
#define __PORTC_P4 PINC4, PORTC, PINC, DDRC
#define PORTC_P4 __PORTC_P4
#define __PORTC_P5 PINC5, PORTC, PINC, DDRC
#define PORTC_P5 __PORTC_P5
#define __PORTC_P6 PINC6, PORTC, PINC, DDRC
#define PORTC_P6 __PORTC_P6
#define __PORTC_P7 PINC7, PORTC, PINC, DDRC
#define PORTC_P7 __PORTC_P7
#endif

#ifdef PORTD
#define __PORTD_P0 PIND0, PORTD, PIND, DDRD
#define PORTD_P0 __PORTD_P0
#define __PORTD_P1 PIND1, PORTD, PIND, DDRD
#define PORTD_P1 __PORTD_P1
#define __PORTD_P2 PIND2, PORTD, PIND, DDRD
#define PORTD_P2 __PORTD_P2
#define __PORTD_P3 PIND3, PORTD, PIND, DDRD
#define PORTD_P3 __PORTD_P3
#define __PORTD_P4 PIND4, PORTD, PIND, DDRD
#define PORTD_P4 __PORTD_P4
#define __PORTD_P5 PIND5, PORTD, PIND, DDRD
#define PORTD_P5 __PORTD_P5
#define __PORTD_P6 PIND6, PORTD, PIND, DDRD
#define PORTD_P6 __PORTD_P6
#define __PORTD_P7 PIND7, PORTD, PIND, DDRD
#define PORTD_P7 __PORTD_P7
#endif

#ifdef PORTE
#define __PORTE_P0 PINE0, PORTE, PINE, DDRE
#define PORTE_P0 __PORTE_P0
#define __PORTE_P1 PINE1, PORTE, PINE, DDRE
#define PORTE_P1 __PORTE_P1
#define __PORTE_P2 PINE2, PORTE, PINE, DDRE
#define PORTE_P2 __PORTE_P2
#define __PORTE_P3 PINE3, PORTE, PINE, DDRE
#define PORTE_P3 __PORTE_P3
#define __PORTE_P4 PINE4, PORTE, PINE, DDRE
#define PORTE_P4 __PORTE_P4
#define __PORTE_P5 PINE5, PORTE, PINE, DDRE
#define PORTE_P5 __PORTE_P5
#define __PORTE_P6 PINE6, PORTE, PINE, DDRE
#define PORTE_P6 __PORTE_P6
#define __PORTE_P7 PINE7, PORTE, PINE, DDRE
#define PORTE_P7 __PORTE_P7
#endif

#ifdef PORTF
#define __PORTF_P0 PINF0, PORTF, PINF, DDRF
#define PORTF_P0 __PORTF_P0
#define __PORTF_P1 PINF1, PORTF, PINF, DDRF
#define PORTF_P1 __PORTF_P1
#define __PORTF_P2 PINF2, PORTF, PINF, DDRF
#define PORTF_P2 __PORTF_P2
#define __PORTF_P3 PINF3, PORTF, PINF, DDRF
#define PORTF_P3 __PORTF_P3
#define __PORTF_P4 PINF4, PORTF, PINF, DDRF
#define PORTF_P4 __PORTF_P4
#define __PORTF_P5 PINF5, PORTF, PINF, DDRF
#define PORTF_P5 __PORTF_P5
#define __PORTF_P6 PINF6, PORTF, PINF, DDRF
#define PORTF_P6 __PORTF_P6
#define __PORTF_P7 PINF7, PORTF, PINF, DDRF
#define PORTF_P7 __PORTF_P7
#endif

#ifdef PORTG
#define __PORTG_P0 PING0, PORTG, PING, DDRG
#define PORTG_P0 __PORTG_P0
#define __PORTG_P1 PING1, PORTG, PING, DDRG
#define PORTG_P1 __PORTG_P1
#define __PORTG_P2 PING2, PORTG, PING, DDRG
#define PORTG_P2 __PORTG_P2
#define __PORTG_P3 PING3, PORTG, PING, DDRG
#define PORTG_P3 __PORTG_P3
#define __PORTG_P4 PING4, PORTG, PING, DDRG
#define PORTG_P4 __PORTG_P4
#define __PORTG_P5 PING5, PORTG, PING, DDRG
#define PORTG_P5 __PORTG_P5
#define __PORTG_P6 PING6, PORTG, PING, DDRG
#define PORTG_P6 __PORTG_P6
#define __PORTG_P7 PING7, PORTG, PING, DDRG
#define PORTG_P7 __PORTG_P7
#endif

#ifdef PORTH
#define __PORTH_P0 PINH0, PORTH, PINH, DDRH
#define PORTH_P0 __PORTH_P0
#define __PORTH_P1 PINH1, PORTH, PINH, DDRH
#define PORTH_P1 __PORTH_P1
#define __PORTH_P2 PINH2, PORTH, PINH, DDRH
#define PORTH_P2 __PORTH_P2
#define __PORTH_P3 PINH3, PORTH, PINH, DDRH
#define PORTH_P3 __PORTH_P3
#define __PORTH_P4 PINH4, PORTH, PINH, DDRH
#define PORTH_P4 __PORTH_P4
#define __PORTH_P5 PINH5, PORTH, PINH, DDRH
#define PORTH_P5 __PORTH_P5
#define __PORTH_P6 PINH6, PORTH, PINH, DDRH
#define PORTH_P6 __PORTH_P6
#define __PORTH_P7 PINH7, PORTH, PINH, DDRH
#define PORTH_P7 __PORTH_P7
#endif

#ifdef PORTI
#define __PORTI_P0 PINI0, PORTI, PINI, DDRI
#define PORTI_P0 __PORTI_P0
#define __PORTI_P1 PINI1, PORTI, PINI, DDRI
#define PORTI_P1 __PORTI_P1
#define __PORTI_P2 PINI2, PORTI, PINI, DDRI
#define PORTI_P2 __PORTI_P2
#define __PORTI_P3 PINI3, PORTI, PINI, DDRI
#define PORTI_P3 __PORTI_P3
#define __PORTI_P4 PINI4, PORTI, PINI, DDRI
#define PORTI_P4 __PORTI_P4
#define __PORTI_P5 PINI5, PORTI, PINI, DDRI
#define PORTI_P5 __PORTI_P5
#define __PORTI_P6 PINI6, PORTI, PINI, DDRI
#define PORTI_P6 __PORTI_P6
#define __PORTI_P7 PINI7, PORTI, PINI, DDRI
#define PORTI_P7 __PORTI_P7
#endif

#ifdef PORTJ
#define __PORTJ_P0 PINJ0, PORTJ, PINJ, DDRJ
#define PORTJ_P0 __PORTJ_P0
#define __PORTJ_P1 PINJ1, PORTJ, PINJ, DDRJ
#define PORTJ_P1 __PORTJ_P1
#define __PORTJ_P2 PINJ2, PORTJ, PINJ, DDRJ
#define PORTJ_P2 __PORTJ_P2
#define __PORTJ_P3 PINJ3, PORTJ, PINJ, DDRJ
#define PORTJ_P3 __PORTJ_P3
#define __PORTJ_P4 PINJ4, PORTJ, PINJ, DDRJ
#define PORTJ_P4 __PORTJ_P4
#define __PORTJ_P5 PINJ5, PORTJ, PINJ, DDRJ
#define PORTJ_P5 __PORTJ_P5
#define __PORTJ_P6 PINJ6, PORTJ, PINJ, DDRJ
#define PORTJ_P6 __PORTJ_P6
#define __PORTJ_P7 PINJ7, PORTJ, PINJ, DDRJ
#define PORTJ_P7 __PORTJ_P7
#endif

#ifdef PORTK
#define __PORTK_P0 PINK0, PORTK, PINK, DDRK
#define PORTK_P0 __PORTK_P0
#define __PORTK_P1 PINK1, PORTK, PINK, DDRK
#define PORTK_P1 __PORTK_P1
#define __PORTK_P2 PINK2, PORTK, PINK, DDRK
#define PORTK_P2 __PORTK_P2
#define __PORTK_P3 PINK3, PORTK, PINK, DDRK
#define PORTK_P3 __PORTK_P3
#define __PORTK_P4 PINK4, PORTK, PINK, DDRK
#define PORTK_P4 __PORTK_P4
#define __PORTK_P5 PINK5, PORTK, PINK, DDRK
#define PORTK_P5 __PORTK_P5
#define __PORTK_P6 PINK6, PORTK, PINK, DDRK
#define PORTK_P6 __PORTK_P6
#define __PORTK_P7 PINK7, PORTK, PINK, DDRK
#define PORTK_P7 __PORTK_P7
#endif

#ifdef PORTL
#define __PORTL_P0 PINL0, PORTL, PINL, DDRL
#define PORTL_P0 __PORTL_P0
#define __PORTL_P1 PINL1, PORTL, PINL, DDRL
#define PORTL_P1 __PORTL_P1
#define __PORTL_P2 PINL2, PORTL, PINL, DDRL
#define PORTL_P2 __PORTL_P2
#define __PORTL_P3 PINL3, PORTL, PINL, DDRL
#define PORTL_P3 __PORTL_P3
#define __PORTL_P4 PINL4, PORTL, PINL, DDRL
#define PORTL_P4 __PORTL_P4
#define __PORTL_P5 PINL5, PORTL, PINL, DDRL
#define PORTL_P5 __PORTL_P5
#define __PORTL_P6 PINL6, PORTL, PINL, DDRL
#define PORTL_P6 __PORTL_P6
#define __PORTL_P7 PINL7, PORTL, PINL, DDRL
#define PORTL_P7 __PORTL_P7
#endif


#endif  // AVRMACROLIBRARY_H_INCLUDED
