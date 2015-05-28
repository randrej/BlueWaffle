#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "AvrMacroLibrary.h"
#include "AvrAdc.h"
#include "spiAdc.h"
#include "LedsAndDisplay.h"
#include "IOProcessor.h"

#define TEST_PIN PORTB_P1

int main()
{
  // initializations
  spiAdc_init();
  avrAdc_init();
  lad_init();
  io_init();

  while (1)
  {
    io_inputPoll();
  }
  return 0;
}