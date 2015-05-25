#include "Modes.h"

/*******************************************************************************
 *  public
 ******************************************************************************/
Mode* modes_activeMode;
uint8_t modes_activeMode_index;

Mode modes_modeArray[];
uint8_t modes_modeArray_length;

/*******************************************************************************
 *  private
 ******************************************************************************/


/*******************************************************************************
 *  implementation
 ******************************************************************************/

/*******************************************************************************
 *  common functions
 ******************************************************************************/
void modes_common_doNothing()
{
}

void modes_common_nextMode()
{
  modes_activeMode_index++;
  if (modes_activeMode_index >= modes_modeArray_length)
  {
    modes_activeMode_index = 0;
  }

  modes_activeMode = &modes_modeArray[modes_activeMode_index];
  modes_activeMode->handleChange();
}

void modes_common_prevMode()
{
  modes_activeMode_index--;
  if (modes_activeMode_index)
  {
    modes_activeMode_index--;
  }
  else
  {
    modes_activeMode_index = modes_modeArray_length - 1;
  }

  modes_activeMode = &modes_modeArray[modes_activeMode_index];
  modes_activeMode->handleChange();
}

void modes_common_encIncHandle()
{
  waves_currentWaveformNumber++;
  if (waves_currentWaveformNumber >= waves_waveformArray_length)
  {
    waves_currentWaveformNumber = 0;
  }
  waves_currentWaveformPointer =
    (uint8_t*)pgm_read_word(&waves_waveformArray[waves_currentWaveformNumber]);
  lad_display_hex(waves_currentWaveformNumber);
}

void modes_common_encDecHandle()
{
  waves_currentWaveformNumber--;
  if (waves_currentWaveformNumber)
  {
    waves_currentWaveformNumber--;
  }
  else
  {
    waves_currentWaveformNumber = waves_waveformArray_length - 1;
  }
  waves_currentWaveformPointer =
    (uint8_t*)pgm_read_word(&waves_waveformArray[waves_currentWaveformNumber]);
  lad_display_hex(waves_currentWaveformNumber);
}

void modes_FreqHandle_lp_pot()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_CHANNEL_FREQ];
  spiAdc_setSamplerate(period);
}

void modes_FreqHandle_hp_pot()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_CHANNEL_FREQ];
  period <<= MODES_HP_SHIFT;
  spiAdc_setSamplerate(io_curr_pots[AVR_ADC_CHANNEL_FREQ]);
}

void modes_BitsHandle_pot()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_CHANNEL_BITS];
    shift <<= 5;
    mask >> shift;
    mask << shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_CHANNEL_BITS];
  }
}

void modes_FreqHandle_lp_cv()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_CHANNEL_CV];
  spiAdc_setSamplerate(period);
}

void modes_FreqHandle_hp_cv()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_CHANNEL_CV];
  period <<= MODES_HP_SHIFT;
  spiAdc_setSamplerate(io_curr_pots[AVR_ADC_CHANNEL_CV]);
}

void modes_BitsHandle_cv()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_CHANNEL_CV];
    shift <<= 5;
    mask >> shift;
    mask << shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_CHANNEL_CV];
  }
}

void modes_FreqBitsHandle_hp_cv()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_CHANNEL_CV];
    shift <<= 5;
    mask >> shift;
    mask << shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_CHANNEL_CV];
  }

  uint8_t period = 255 - io_curr_pots[AVR_ADC_CHANNEL_CV];
  period <<= MODES_HP_SHIFT;
  spiAdc_setSamplerate(io_curr_pots[AVR_ADC_CHANNEL_CV]);
}


void modes_FreqBitsHandle_lp_cv()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_CHANNEL_CV];
    shift <<= 5;
    mask >> shift;
    mask << shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_CHANNEL_CV];
  }

  uint8_t period = 255 - io_curr_pots[AVR_ADC_CHANNEL_CV];
  spiAdc_setSamplerate(period);
}


void modes_common_switchBitsHandle()
{
  io_curr_bits_sw = io_curr_bits_sw;
}

/*******************************************************************************
 *  Python-assisted automatic code generation starts here!
 *
 *  See here how to download and install cog:
 *  http://nedbatchelder.com/code/cog/
 *
 *  When you run cog like this:
 *
 *  python -m cogapp -r Modes.c
 *
 *  it regenerates the mode array and modes
 ******************************************************************************/

/* [[[cog
import cog

# generating access functions
def generateMode(code):
  """ A generate the mode functions and struct from a bitvector"""

  # extract the parameters from bitvector
  hiPrecFreq = False
  preBits = False
  cvFreq = False
  cvBits = False

  if code & 0b0001:
    hiPrecFreq = True
  if code & 0b0010:
    preBits = True
  if code & 0b0100:
    cvFreq = True
  if code & 0b1000:
    cvBits = True

  # determine freq precision
  precision = 'lp'
  if hiPrecFreq:
    precision = 'hp'

  # generate the handler for freq pot, if it's not covered by CV
  freqHandle = ''
  if cvFreq:
    freqHandle = 'modes_common_doNothing'
  else:
    freqHandle = 'modes_FreqHandle_'
    freqHandle += precision + '_pot'

  # generate the handler for bits pot, if it's not covered by CV
  bitsHandle = ''
  if cvBits:
    bitsHandle = 'modes_common_doNothing'
  else:
    bitsHandle = 'modes_BitsHandle_pot'

  # generate the handler for CV
  cvHandle = 'modes_common_doNothing'
  if cvFreq and cvBits:
    cvHandle = 'modes_FreqBitsHandle_'+precision+'_cv'
  elif cvFreq:
    cvHandle = 'modes_FreqHandle_'+precision+'_cv'
  elif cvBits:
    cvHandle = 'modes_BitsHandle_'+precision+'_cv'

  #generate handlechange function:
  cog.outl('//MODE '+str(code))
  cog.outl('void modes_mode'+str(code)+'_handleChange()')
  cog.outl('{')
  cog.outl('  modes_common_switchBitsHandle();')
  handlers = [freqHandle, bitsHandle, cvHandle]
  for s in handlers:
    if s!='modes_common_doNothing':
      cog.outl('  ' + s + "();")
  if preBits:
    cog.outl('  spiAdc_bitmask_before = 1;')
  else:
    cog.outl('  spiAdc_bitmask_before = 0;')
  cog.outl('}')

  #generate mode struct
  cog.outl('Mode modes_mode'+str(code)+'_struct = {')
  cog.outl('  &modes_common_doNothing,')
  cog.outl('  &modes_mode'+str(code)+'_handleChange,')
  cog.outl('  &' + freqHandle + ',')
  cog.outl('  &' + bitsHandle + ',')
  cog.outl('  &' + cvHandle + ',')
  cog.outl('  &modes_common_switchBitsHandle, ')
  cog.outl('  &modes_common_nextMode, ')
  cog.outl('  &modes_common_encIncHandle, ')
  cog.outl('  &modes_common_encDecHandle ')
  cog.outl('};')


for num in range(0, 0b1111):
  generateMode(num)

cog.outl()
cog.outl()

cog.out('Mode modes_modeArray[15] = {')
modeArr = []
for num in range(0, 0b1111+1):
  modeArr.append('modes_mode'+str(num)+'_struct')
cog.out(', '.join(modeArr))
cog.outl('};')

cog.out('uint8_t modes_modeArray_length = 15;')
]]] */
// MODE 0
void modes_mode0_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode0_struct = {
  &modes_common_doNothing,   &modes_mode0_handleChange,
  &modes_FreqHandle_lp_pot,  &modes_BitsHandle_pot,
  &modes_common_doNothing,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 1
void modes_mode1_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode1_struct = {
  &modes_common_doNothing,   &modes_mode1_handleChange,
  &modes_FreqHandle_hp_pot,  &modes_BitsHandle_pot,
  &modes_common_doNothing,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 2
void modes_mode2_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode2_struct = {
  &modes_common_doNothing,   &modes_mode2_handleChange,
  &modes_FreqHandle_lp_pot,  &modes_BitsHandle_pot,
  &modes_common_doNothing,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 3
void modes_mode3_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode3_struct = {
  &modes_common_doNothing,   &modes_mode3_handleChange,
  &modes_FreqHandle_hp_pot,  &modes_BitsHandle_pot,
  &modes_common_doNothing,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 4
void modes_mode4_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_lp_cv();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode4_struct = {
  &modes_common_doNothing,   &modes_mode4_handleChange,
  &modes_common_doNothing,   &modes_BitsHandle_pot,
  &modes_FreqHandle_lp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 5
void modes_mode5_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_hp_cv();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode5_struct = {
  &modes_common_doNothing,   &modes_mode5_handleChange,
  &modes_common_doNothing,   &modes_BitsHandle_pot,
  &modes_FreqHandle_hp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 6
void modes_mode6_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_lp_cv();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode6_struct = {
  &modes_common_doNothing,   &modes_mode6_handleChange,
  &modes_common_doNothing,   &modes_BitsHandle_pot,
  &modes_FreqHandle_lp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 7
void modes_mode7_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_hp_cv();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode7_struct = {
  &modes_common_doNothing,   &modes_mode7_handleChange,
  &modes_common_doNothing,   &modes_BitsHandle_pot,
  &modes_FreqHandle_hp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 8
void modes_mode8_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_lp_cv();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode8_struct = {
  &modes_common_doNothing,   &modes_mode8_handleChange,
  &modes_FreqHandle_lp_pot,  &modes_common_doNothing,
  &modes_BitsHandle_lp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 9
void modes_mode9_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_hp_cv();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode9_struct = {
  &modes_common_doNothing,   &modes_mode9_handleChange,
  &modes_FreqHandle_hp_pot,  &modes_common_doNothing,
  &modes_BitsHandle_hp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 10
void modes_mode10_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_lp_cv();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode10_struct = {
  &modes_common_doNothing,   &modes_mode10_handleChange,
  &modes_FreqHandle_lp_pot,  &modes_common_doNothing,
  &modes_BitsHandle_lp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 11
void modes_mode11_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_hp_cv();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode11_struct = {
  &modes_common_doNothing,   &modes_mode11_handleChange,
  &modes_FreqHandle_hp_pot,  &modes_common_doNothing,
  &modes_BitsHandle_hp_cv,   &modes_common_switchBitsHandle,
  &modes_common_nextMode,    &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 12
void modes_mode12_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqBitsHandle_lp_cv();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode12_struct = {
  &modes_common_doNothing,     &modes_mode12_handleChange,
  &modes_common_doNothing,     &modes_common_doNothing,
  &modes_FreqBitsHandle_lp_cv, &modes_common_switchBitsHandle,
  &modes_common_nextMode,      &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 13
void modes_mode13_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqBitsHandle_hp_cv();
  spiAdc_bitmask_before = 0;
}
Mode modes_mode13_struct = {
  &modes_common_doNothing,     &modes_mode13_handleChange,
  &modes_common_doNothing,     &modes_common_doNothing,
  &modes_FreqBitsHandle_hp_cv, &modes_common_switchBitsHandle,
  &modes_common_nextMode,      &modes_common_encIncHandle,
  &modes_common_encDecHandle};
// MODE 14
void modes_mode14_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqBitsHandle_lp_cv();
  spiAdc_bitmask_before = 1;
}
Mode modes_mode14_struct = {
  &modes_common_doNothing,     &modes_mode14_handleChange,
  &modes_common_doNothing,     &modes_common_doNothing,
  &modes_FreqBitsHandle_lp_cv, &modes_common_switchBitsHandle,
  &modes_common_nextMode,      &modes_common_encIncHandle,
  &modes_common_encDecHandle};


Mode modes_modeArray[15] = {
  modes_mode0_struct,  modes_mode1_struct,  modes_mode2_struct,
  modes_mode3_struct,  modes_mode4_struct,  modes_mode5_struct,
  modes_mode6_struct,  modes_mode7_struct,  modes_mode8_struct,
  modes_mode9_struct,  modes_mode10_struct, modes_mode11_struct,
  modes_mode12_struct, modes_mode13_struct, modes_mode14_struct,
  modes_mode15_struct};
uint8_t modes_modeArray_length = 15;
// [[[end]]]
