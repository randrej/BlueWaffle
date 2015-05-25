#include "LedsAndDisplay.h"
/*******************************************************************************
 *  Public
 ******************************************************************************/
volatile uint8_t lad_ledsArray[3] = {67, 69, 70};
uint8_t lad_flashPins[3] = {LAD_LEDS, LAD_DISPLAY_MSD, LAD_DISPLAY_LSD};


/*******************************************************************************
 *  Private
 ******************************************************************************/
volatile uint8_t lad_currentIndex;


/*******************************************************************************
 *  Progmem
 ******************************************************************************/
const uint8_t lad_decDigits[11] PROGMEM = {
  0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110,
  0b10111110, 0b11100000, 0b11111110, 0b11110110, 0b10011111};

const uint8_t lad_hexDigits[16] PROGMEM = {
  0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110,
  0b10111110, 0b11100000, 0b11111110, 0b11110110, 0b11101110, 0b111110,
  0b10011100, 0b1111010,  0b10011110, 0b10001110};

/*******************************************************************************
*  Implementation
******************************************************************************/
void lad_init()
{
	SETBITMASK(LAD_OUT_DIR, 0b11111111);
	SETBITMASK(LAD_PINS_DIR, LAD_PINS_MASK);
}

void lad_display_dec(uint8_t number)
{
  uint8_t LSDigit = number % 10;
  uint8_t MSDigit = (number / 10) % 10;


  lad_ledsArray[1] = pgm_read_byte(&lad_decDigits[LSDigit]);
  lad_ledsArray[2] = pgm_read_byte(&lad_decDigits[MSDigit]);
}

void lad_display_hex(uint8_t number)
{
  uint8_t LSDigit = number % 16;
  uint8_t MSDigit = (number / 16) % 16;

  lad_ledsArray[1] = pgm_read_byte(&lad_hexDigits[LSDigit]);
  lad_ledsArray[2] = pgm_read_byte(&lad_hexDigits[MSDigit]);

  // lad_ledsArray[1] = LSDigit;
  // lad_ledsArray[2] = MSDigit;

}