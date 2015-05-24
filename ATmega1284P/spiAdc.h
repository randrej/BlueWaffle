#ifndef SPI_ADC_H
#define SPI_ADC_H

#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "AvrMacroLibrary.h"
#include "Waveforms.h"


/*******************************************************************************
 *  SPI settings and registers
 ******************************************************************************/
#define SPI_PRESCALER 2

#define SPI_MOSI_PIN PORTB_P5
#define SPI_MISO_PIN PORTB_P6
#define SPI_SCK_PIN PORTB_P7

#define SPI_ADC_CS PORTB_P0

#define C_SPI_ENABLE SPCR, SPE             // SPI Enable
#define C_SPI_INTERRUPT_ENABLE SPCR, SPIE  // SPI Interupt Enable
#define C_SPI_LSBFIRST SPCR, DORD  // Data Order (0:MSB first / 1:LSB first)
#define C_SPI_MASTER SPCR, MSTR    // Master/Slave select

#define C_SPI_TRANSFER_COMPLETE SPSR, SPIF  // Transfer complete flag


#define C_SPI_SPR0 SPCR, SPR0    // SPI Clock Rate 0
#define C_SPI_SPR1 SPCR, SPR1    // SPI Clock Rate 1
#define C_SPI_SPI2X SPSR, SPI2X  // Double Clock Rate
#define C_SPI_CPOL                                                             \
  SPCR, CPOL  // Clock Polarity (0:SCK low / 1:SCK hi when idle)
#define C_SPI_CPHA                                                             \
  SPCR, CPHA  // Clock Phase (0:leading / 1:trailing edge sampling)

/*******************************************************************************
 *  Timer0 settings and registers
 ******************************************************************************/

// 16MHz / 256 = 62.5KHz
#define SPI_ADC_TIMER0_PRESCALE 256

// Timer0 OC0A behavior
#define C_TIMER0_COM0A0 TCCR0A, COM0A0
#define C_TIMER0_COM0A1 TCCR0A, COM0A1
// Timer0 OC0B behavior
#define C_TIMER0_COM0B0 TCCR0A, COM0B0
#define C_TIMER0_COM0B1 TCCR0A, COM0B1

#define C_TIMER0_WGM00 TCCR0A, WGM00
#define C_TIMER0_WGM01 TCCR0A, WGM01
#define C_TIMER0_WGM02 TCCR0B, WGM02

// Timer0 clock source / prescaler
#define C_TIMER0_CS00 TCCR0B, CS00
#define C_TIMER0_CS01 TCCR0B, CS01
#define C_TIMER0_CS02 TCCR0B, CS02

// Timer0 comparison - maximum
#define TIMER0_COMPARISON_A OCR0A
#define TIMER0_COMPARISON_B OCR0B

// Timer0 comparison counter register
#define TIMER0_COUNT_REGISTER TCNT0

// Timer0 comparison interrupts
#define C_TIMER0_MATCH_B_INTERRUPT_ENABLE TIMSK0, OCIE0B
#define C_TIMER0_MATCH_A_INTERRUPT_ENABLE TIMSK0, OCIE0A
#define C_TIMER0_OVERFLOW_INTERRUPT_ENABLE TIMSK0, TOIE0

// Timer0 interrupt flags
#define C_TIMER0_MATCH_B_INTERRUPT_FLAG TIFR0, OCF0B
#define C_TIMER0_MATCH_A_INTERRUPT_FLAG TIFR0, OCF0A
#define C_TIMER0_OVERFLOW_INTERRUPT_FLAG TIFR0, TOV0

/*******************************************************************************
 *  Interface
 ******************************************************************************/

void spiAdc_init(void);
void spiAdc_setSamplerate(uint8_t samplerate);

extern volatile uint8_t spiAdc_bitmask;
extern volatile uint8_t spiAdc_bitmask_before;

#endif