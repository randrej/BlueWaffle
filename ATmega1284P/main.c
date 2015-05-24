#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


#include "AvrAdc.h"
#include "spiAdc.h"
#include "LedsAndDisplay.h"
#include "AvrMacroLibrary.h"

#define TEST_PIN PORTB_P1

int main()
{
  // initializations
  spiAdc_init();
  avrAdc_init();
  lad_init();
  lad_display_hex(12);
  SETBITMASK(DDRD, 0b11111111);
  SETBITMASK(DDRC, 0b11111111);
  // PC_SET_OUTPUT(TEST_PIN);
  while (1)
  {
    // spiAdc_sampleAndProcess();
  }
  return 0;
}