#include "Waveforms.h"


/*******************************************************************************
 *  public
 ******************************************************************************/
uint8_t waves_currentWaveformNumber;
uint8_t* waves_currentWaveformPointer;

/*******************************************************************************
 *  Python-assisted automatic code generation starts here!
 *
 *	See here how to download and install cog:
 *	http://nedbatchelder.com/code/cog/
 *
 *	When you run cog like this:

 *	python -m cogapp -r Waveforms.c
 *
 *	a JSON file called Waveforms.json gets parsed and C code for the waveforms
 *	it contains is automatically generated.
 *
 *	The JSON file is structured like this:
 *  {
 *     "waveforms": [
 *         {
 *             "name": "<waveform's name or formula or whatever>",
 *             "waveform": [
 *								<256 unsigned bytes representing the waveform>
 *             ]
 *         },
 *         {
 *             "name": "<waveform's name or formula or whatever>",
 *             "waveform": [
 * 								<256 unsigned bytes representing the waveform>
 *             ]
 *         },
 *				 <... up to 252 waveforms>
 *     ]
 * }
 *
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

// test
const uint8_t waves_waveform0[256] PROGMEM = {
  128, 125, 122, 119, 116, 113, 110, 107, 104, 100, 97,  94,  91,  88,  85,
  82,  80,  77,  74,  71,  68,  65,  63,  60,  57,  55,  52,  50,  47,  45,
  43,  40,  38,  36,  34,  32,  30,  28,  26,  24,  22,  20,  19,  17,  16,
  14,  13,  11,  10,  9,   8,   7,   6,   5,   4,   4,   3,   2,   2,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   3,   4,   4,
  5,   6,   7,   8,   9,   10,  11,  13,  14,  16,  17,  19,  20,  22,  24,
  26,  28,  30,  32,  34,  36,  38,  40,  43,  45,  47,  50,  52,  55,  57,
  60,  63,  65,  68,  71,  74,  77,  80,  82,  85,  88,  91,  94,  97,  100,
  104, 107, 110, 113, 116, 119, 122, 125, 129, 132, 135, 138, 141, 144, 147,
  150, 153, 157, 160, 163, 166, 169, 172, 175, 177, 180, 183, 186, 189, 192,
  194, 197, 200, 202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225, 227,
  229, 231, 233, 235, 237, 238, 240, 241, 243, 244, 246, 247, 248, 249, 250,
  251, 252, 253, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 254, 253, 253, 252, 251, 250, 249, 248, 247, 246,
  244, 243, 241, 240, 238, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219,
  217, 214, 212, 210, 207, 205, 202, 200, 197, 194, 192, 189, 186, 183, 180,
  177, 175, 172, 169, 166, 163, 160, 157, 153, 150, 147, 144, 141, 138, 135,
  132}

// test
const uint8_t waves_waveform1[256] PROGMEM = {
  128, 125, 122, 119, 116, 113, 110, 107, 104, 100, 97,  94,  91,  88,  85,
  82,  80,  77,  74,  71,  68,  65,  63,  60,  57,  55,  52,  50,  47,  45,
  43,  40,  38,  36,  34,  32,  30,  28,  26,  24,  22,  20,  19,  17,  16,
  14,  13,  11,  10,  9,   8,   7,   6,   5,   4,   4,   3,   2,   2,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   3,   4,   4,
  5,   6,   7,   8,   9,   10,  11,  13,  14,  16,  17,  19,  20,  22,  24,
  26,  28,  30,  32,  34,  36,  38,  40,  43,  45,  47,  50,  52,  55,  57,
  60,  63,  65,  68,  71,  74,  77,  80,  82,  85,  88,  91,  94,  97,  100,
  104, 107, 110, 113, 116, 119, 122, 125, 129, 132, 135, 138, 141, 144, 147,
  150, 153, 157, 160, 163, 166, 169, 172, 175, 177, 180, 183, 186, 189, 192,
  194, 197, 200, 202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225, 227,
  229, 231, 233, 235, 237, 238, 240, 241, 243, 244, 246, 247, 248, 249, 250,
  251, 252, 253, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 254, 253, 253, 252, 251, 250, 249, 248, 247, 246,
  244, 243, 241, 240, 238, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219,
  217, 214, 212, 210, 207, 205, 202, 200, 197, 194, 192, 189, 186, 183, 180,
  177, 175, 172, 169, 166, 163, 160, 157, 153, 150, 147, 144, 141, 138, 135,
  132}

// waveformArray
const uint8_t* waves_waveformArray[2] PROGMEM = {waves_waveform0,
                                                 waves_waveform1};
uint8_t waves_waveformArray_length = 2;
// [[[end]]]

/*******************************************************************************
 *  Python-assisted automatic code generation ends here!
 ******************************************************************************/

/*******************************************************************************
 *  implementation
 ******************************************************************************/

void waves_init()
{
  waves_currentWaveformNumber = 0;
  waves_currentWaveformPointer =
    (uint8_t*)pgm_read_word(&waves_waveformArray[waves_currentWaveformNumber]);
}