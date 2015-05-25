#include "spiAdc.h"


/*******************************************************************************
 *  Public
 ******************************************************************************/
volatile uint8_t spiAdc_bitmask = 0xFF;
volatile uint8_t spiAdc_bitmask_before;


/*******************************************************************************
 *  Private
 ******************************************************************************/
uint8_t wavetable[] = {
  2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,
  5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,   8,   9,   9,   9,
  10,  10,  10,  11,  11,  12,  12,  13,  13,  13,  14,  15,  15,  16,  16,
  17,  17,  18,  19,  19,  20,  21,  22,  22,  23,  24,  25,  26,  27,  28,
  29,  30,  31,  32,  33,  34,  35,  36,  38,  39,  40,  42,  43,  44,  46,
  47,  49,  50,  52,  54,  55,  57,  59,  61,  62,  64,  66,  68,  70,  72,
  74,  76,  78,  80,  83,  85,  87,  89,  92,  94,  96,  99,  101, 103, 106,
  108, 111, 113, 116, 118, 121, 123, 126, 128, 130, 133, 135, 138, 140, 143,
  145, 148, 150, 153, 155, 157, 160, 162, 164, 167, 169, 171, 173, 176, 178,
  180, 182, 184, 186, 188, 190, 192, 194, 195, 197, 199, 201, 202, 204, 206,
  207, 209, 210, 212, 213, 214, 216, 217, 218, 220, 221, 222, 223, 224, 225,
  226, 227, 228, 229, 230, 231, 232, 233, 234, 234, 235, 236, 237, 237, 238,
  239, 239, 240, 240, 241, 241, 242, 243, 243, 243, 244, 244, 245, 245, 246,
  246, 246, 247, 247, 247, 248, 248, 248, 249, 249, 249, 249, 250, 250, 250,
  250, 251, 251, 251, 251, 251, 252, 252, 252, 252, 252, 252, 252, 253, 253,
  253, 253, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254,
  254};


void spiAdc_init(void)
{
  // IO initialization
  //----------------------------------------------------------------------------

  // DAC out
  SETBITMASK(DDRC, 0b11111111);  // set portc to outuput for DAC

  // ADC pins
  PC_SET_OUTPUT(SPI_ADC_CS);
  PC_SET(SPI_ADC_CS);

  // SPI initialization
  //----------------------------------------------------------------------------

  // setting pin I/O
  PC_SET_OUTPUT(SPI_MOSI_PIN);
  PC_SET_INPUT(SPI_MISO_PIN);
  PC_SET_OUTPUT(SPI_SCK_PIN);

  // disable for configuration
  C_CLEARBIT(C_SPI_ENABLE);

  C_CLEARBIT(C_SPI_INTERRUPT_ENABLE);
  C_CLEARBIT(C_SPI_LSBFIRST);

  C_CLEARBIT(C_SPI_CPOL);  // polarity - normal low
  C_CLEARBIT(C_SPI_CPHA);  // leading edge sampling

// prescaler settings
#if SPI_PRESCALER == 4
  C_CLEARBIT(C_SPI_SPR0);
  C_CLEARBIT(C_SPI_SPR1);
  C_CLEARBIT(C_SPI_SPI2X);
#endif
#if SPI_PRESCALER == 16
  C_SETBIT(C_SPI_SPR0);
  C_CLEARBIT(C_SPI_SPR1);
  C_CLEARBIT(C_SPI_SPI2X);
#endif
#if SPI_PRESCALER == 64
  C_CLEARBIT(C_SPI_SPR0);
  C_SETBIT(C_SPI_SPR1);
  C_CLEARBIT(C_SPI_SPI2X);
#endif
#if SPI_PRESCALER == 128
  C_SETBIT(C_SPI_SPR0);
  C_SETBIT(C_SPI_SPR1);
  C_CLEARBIT(C_SPI_SPI2X);
#endif
#if SPI_PRESCALER == 2
  C_CLEARBIT(C_SPI_SPR0);
  C_CLEARBIT(C_SPI_SPR1);
  C_SETBIT(C_SPI_SPI2X);
#endif
#if SPI_PRESCALER == 8
  C_SETBIT(C_SPI_SPR0);
  C_CLEARBIT(C_SPI_SPR1);
  C_SETBIT(C_SPI_SPI2X);
#endif
#if SPI_PRESCALER == 32
  C_CLEARBIT(C_SPI_SPR0);
  C_SETBIT(C_SPI_SPR1);
  C_SETBIT(C_SPI_SPI2X);
#endif

  // enable master
  C_CLEARBIT(C_SPI_TRANSFER_COMPLETE);
  C_SETBIT(C_SPI_MASTER);
  C_SETBIT(C_SPI_ENABLE);

  // Timer0 initialization
  //----------------------------------------------------------------------------


  // /256 prescaler
  // 16MHz / 256 = 62.5KHz
  C_CLEARBIT(C_TIMER0_CS00);
  C_CLEARBIT(C_TIMER0_CS01);
  C_SETBIT(C_TIMER0_CS02);

  // initial samplerate
  spiAdc_setSamplerate(0);

  // enable timer interrupts
  C_CLEARBIT(C_TIMER0_MATCH_B_INTERRUPT_ENABLE);
  C_SETBIT(C_TIMER0_MATCH_A_INTERRUPT_ENABLE);
  C_CLEARBIT(C_TIMER0_OVERFLOW_INTERRUPT_ENABLE);

  // clear timer interrupts
  C_CLEARBIT(C_TIMER0_MATCH_B_INTERRUPT_FLAG);
  C_CLEARBIT(C_TIMER0_MATCH_A_INTERRUPT_FLAG);
  C_CLEARBIT(C_TIMER0_OVERFLOW_INTERRUPT_FLAG);

  // CTC mode - enable
  C_CLEARBIT(C_TIMER0_WGM00);
  C_SETBIT(C_TIMER0_WGM01);
  C_CLEARBIT(C_TIMER0_WGM02);

  sei();  // enable global interrupts
}

void spiAdc_setSamplerate(uint8_t samplerate)
{
  ATOMIC_BLOCK(ATOMIC_FORCEON)
  {
    TIMER0_COMPARISON_A = samplerate;
    if (TIMER0_COUNT_REGISTER > samplerate)
    {
      TIMER0_COUNT_REGISTER = samplerate;
    }
  }
}


ISR(TIMER0_COMPA_vect)
{
  PC_CLEAR(SPI_ADC_CS);  // init conversion
  SPDR = 0;
  while (!C_CHECKBIT(C_SPI_TRANSFER_COMPLETE))
    ;
  volatile uint8_t byte0 = SPDR;

  SPDR = 0;
  while (!C_CHECKBIT(C_SPI_TRANSFER_COMPLETE))
    ;
  volatile uint8_t byte1 = SPDR;

  volatile uint8_t input = (byte0 << 3) | (byte1 >> 5);

  // TODO: replace with bitcode
  if (spiAdc_bitmask_before)
  {
    PORTC =
      pgm_read_byte(&waves_currentWaveformPointer[input & spiAdc_bitmask]);
  }
  else
  {
    PORTC =
      pgm_read_byte(&waves_currentWaveformPointer[input]) & spiAdc_bitmask;
  }

  PC_SET(SPI_ADC_CS);  // end conversion
}
