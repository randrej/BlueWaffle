#include "Modes.h"

/*******************************************************************************
 *  public
 ******************************************************************************/
Mode* modes_activeMode;
uint8_t modes_activeMode_index;

/*******************************************************************************
 *  private
 ******************************************************************************/


/*******************************************************************************
 *  implementation
 ******************************************************************************/

/*******************************************************************************
 *  common functions
 ******************************************************************************/
void modes_init()
{
  modes_activeMode = &modes_modeArray[modes_activeMode_index];
  modes_activeMode->handleChange();

  waves_currentWaveformNumber = 0;
  waves_currentWaveformPointer =
    (uint8_t*)pgm_read_word(&waves_waveformArray[waves_currentWaveformNumber]);
  lad_display_hex(waves_currentWaveformNumber);
}


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
  uint8_t period = 255 - io_curr_pots[AVR_ADC_INDEX_FREQ];
  spiAdc_setSamplerate(period);
}

void modes_FreqHandle_hp_pot()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_INDEX_FREQ];
  period <<= MODES_HP_SHIFT;
  spiAdc_setSamplerate(io_curr_pots[AVR_ADC_INDEX_FREQ]);
}

void modes_BitsHandle_pot()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_INDEX_BITS];
    shift <<= 5;
    mask >>= shift;
    mask <<= shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_INDEX_BITS];
  }
}

void modes_FreqHandle_lp_cv()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_INDEX_CV];
  spiAdc_setSamplerate(period);
}

void modes_FreqHandle_hp_cv()
{
  uint8_t period = 255 - io_curr_pots[AVR_ADC_INDEX_CV];
  period <<= MODES_HP_SHIFT;
  spiAdc_setSamplerate(io_curr_pots[AVR_ADC_INDEX_CV]);
}

void modes_BitsHandle_cv()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_INDEX_CV];
    shift <<= 5;
    mask >>= shift;
    mask <<= shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_INDEX_CV];
  }
}

void modes_FreqBitsHandle_hp_cv()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_INDEX_CV];
    shift <<= 5;
    mask >>= shift;
    mask <<= shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_INDEX_CV];
  }

  uint8_t period = 255 - io_curr_pots[AVR_ADC_INDEX_CV];
  period <<= MODES_HP_SHIFT;
  spiAdc_setSamplerate(io_curr_pots[AVR_ADC_INDEX_CV]);
}


void modes_FreqBitsHandle_lp_cv()
{
  if (io_curr_bits_sw)
  {
    uint8_t mask = 0xFF;
    uint8_t shift = io_curr_pots[AVR_ADC_INDEX_CV];
    shift <<= 5;
    mask >>= shift;
    mask <<= shift;
    spiAdc_bitmask = mask;
  }
  else
  {
    spiAdc_bitmask = io_curr_pots[AVR_ADC_INDEX_CV];
  }

  uint8_t period = 255 - io_curr_pots[AVR_ADC_INDEX_CV];
  spiAdc_setSamplerate(period);
}


void modes_common_switchBitsHandle()
{
  io_curr_bits_sw = io_curr_bits_sw;
}


// TODO: generate LED patterns

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
    cvHandle = 'modes_BitsHandle_cv'

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

  #return mode struct
  modeStruct = ''
  modeStruct += '{'
  modeStruct += '  &modes_common_doNothing,'
  modeStruct += '  &modes_mode'+str(code)+'_handleChange,'
  modeStruct += '  &' + freqHandle + ','
  modeStruct += '  &' + bitsHandle + ','
  modeStruct += '  &' + cvHandle + ','
  modeStruct += '  &modes_common_switchBitsHandle, '
  modeStruct += '  &modes_common_nextMode, '
  modeStruct += '  &modes_common_encIncHandle, '
  modeStruct += '  &modes_common_encDecHandle '
  modeStruct += '}'

  return modeStruct

# generate handleChange functions and save structs for later
modeStructs = []
for num in range(0, 0b1111):
  modeStructs.append(generateMode(num))

cog.outl()
cog.outl()

cog.out('Mode modes_modeArray[15] = {')
cog.out(', \n'.join(modeStructs))
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
// MODE 1
void modes_mode1_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 0;
}
// MODE 2
void modes_mode2_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 1;
}
// MODE 3
void modes_mode3_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_pot();
  spiAdc_bitmask_before = 1;
}
// MODE 4
void modes_mode4_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_lp_cv();
  spiAdc_bitmask_before = 0;
}
// MODE 5
void modes_mode5_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_hp_cv();
  spiAdc_bitmask_before = 0;
}
// MODE 6
void modes_mode6_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_lp_cv();
  spiAdc_bitmask_before = 1;
}
// MODE 7
void modes_mode7_handleChange()
{
  modes_common_switchBitsHandle();
  modes_BitsHandle_pot();
  modes_FreqHandle_hp_cv();
  spiAdc_bitmask_before = 1;
}
// MODE 8
void modes_mode8_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_cv();
  spiAdc_bitmask_before = 0;
}
// MODE 9
void modes_mode9_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_cv();
  spiAdc_bitmask_before = 0;
}
// MODE 10
void modes_mode10_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_lp_pot();
  modes_BitsHandle_cv();
  spiAdc_bitmask_before = 1;
}
// MODE 11
void modes_mode11_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqHandle_hp_pot();
  modes_BitsHandle_cv();
  spiAdc_bitmask_before = 1;
}
// MODE 12
void modes_mode12_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqBitsHandle_lp_cv();
  spiAdc_bitmask_before = 0;
}
// MODE 13
void modes_mode13_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqBitsHandle_hp_cv();
  spiAdc_bitmask_before = 0;
}
// MODE 14
void modes_mode14_handleChange()
{
  modes_common_switchBitsHandle();
  modes_FreqBitsHandle_lp_cv();
  spiAdc_bitmask_before = 1;
}


Mode modes_modeArray[15] = {
  {&modes_common_doNothing, &modes_mode0_handleChange, &modes_FreqHandle_lp_pot,
   &modes_BitsHandle_pot, &modes_common_doNothing,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode1_handleChange, &modes_FreqHandle_hp_pot,
   &modes_BitsHandle_pot, &modes_common_doNothing,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode2_handleChange, &modes_FreqHandle_lp_pot,
   &modes_BitsHandle_pot, &modes_common_doNothing,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode3_handleChange, &modes_FreqHandle_hp_pot,
   &modes_BitsHandle_pot, &modes_common_doNothing,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode4_handleChange, &modes_common_doNothing,
   &modes_BitsHandle_pot, &modes_FreqHandle_lp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode5_handleChange, &modes_common_doNothing,
   &modes_BitsHandle_pot, &modes_FreqHandle_hp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode6_handleChange, &modes_common_doNothing,
   &modes_BitsHandle_pot, &modes_FreqHandle_lp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode7_handleChange, &modes_common_doNothing,
   &modes_BitsHandle_pot, &modes_FreqHandle_hp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode8_handleChange, &modes_FreqHandle_lp_pot,
   &modes_common_doNothing, &modes_BitsHandle_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode9_handleChange, &modes_FreqHandle_hp_pot,
   &modes_common_doNothing, &modes_BitsHandle_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode10_handleChange,
   &modes_FreqHandle_lp_pot, &modes_common_doNothing, &modes_BitsHandle_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode11_handleChange,
   &modes_FreqHandle_hp_pot, &modes_common_doNothing, &modes_BitsHandle_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode12_handleChange, &modes_common_doNothing,
   &modes_common_doNothing, &modes_FreqBitsHandle_lp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode13_handleChange, &modes_common_doNothing,
   &modes_common_doNothing, &modes_FreqBitsHandle_hp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle},
  {&modes_common_doNothing, &modes_mode14_handleChange, &modes_common_doNothing,
   &modes_common_doNothing, &modes_FreqBitsHandle_lp_cv,
   &modes_common_switchBitsHandle, &modes_common_nextMode,
   &modes_common_encIncHandle, &modes_common_encDecHandle}};
uint8_t modes_modeArray_length = 15;
// [[[end]]]
