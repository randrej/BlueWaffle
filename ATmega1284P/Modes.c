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
import cog, json

with open('Waveforms.json') as data_file:
  data = json.load(data_file)

waveList = []
nrOfWaves = 0

cog.outl('')


for idx, wf in enumerate(data['waveforms']):
  cog.outl('// ' + wf['name'])
  cog.out('const uint8_t waves_waveform' + str(idx) + '[256] PROGMEM = {')
  cog.out(str(wf['waveform'])[1:-1])
  cog.outl('}')
  cog.outl()
  waveList.append('waves_waveform' + str(idx))
  nrOfWaves += 1

cog.outl("// waveformArray")
cog.out("const uint8_t* waves_waveformArray["+ str(nrOfWaves) +"] PROGMEM = {")
cog.outl(', '.join(waveList) + "};")

cog.outl("uint8_t waves_waveformArray_length = "+ str(nrOfWaves) +";")
]]] */