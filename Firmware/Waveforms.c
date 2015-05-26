#include "Waveforms.h"


/*******************************************************************************
 *  public
 ******************************************************************************/
uint8_t waves_currentWaveformNumber;
uint8_t* waves_currentWaveformPointer;

/*******************************************************************************
 *  Python-assisted automatic code generation starts here!
 *
 *  See here how to download and install cog:
 *  http://nedbatchelder.com/code/cog/
 *
 *  When you run cog like this:

 *  python -m cogapp -r Waveforms.c
 *
 *  a JSON file called Waveforms.json gets parsed and C code for the waveforms
 *  it contains is automatically generated.
 *
 *  The JSON file is structured like this:
 *  {
 *     "waveforms": [
 *         {
 *             "name": "<waveform's name or formula or whatever>",
 *             "waveform": [
 *                <256 unsigned bytes representing the waveform>
 *             ]
 *         },
 *         {
 *             "name": "<waveform's name or formula or whatever>",
 *             "waveform": [
 *                <256 unsigned bytes representing the waveform>
 *             ]
 *         },
 *         <... up to 252 waveforms>
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
  cog.outl('};')
  cog.outl()
  waveList.append('waves_waveform' + str(idx))
  nrOfWaves += 1

cog.outl("// waveformArray")
cog.out("const uint8_t* waves_waveformArray["+ str(nrOfWaves) +"] PROGMEM = {")
cog.outl(', '.join(waveList) + "};")

cog.outl("uint8_t waves_waveformArray_length = "+ str(nrOfWaves) +";")


]]] */

// linear: f(x) = x
const uint8_t waves_waveform0[256] PROGMEM = {
  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,
  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100, 101, 102, 103, 104,
  105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
  120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
  135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
  150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
  165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
  180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
  195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
  210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
  225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
  255};

// sin(xs)
const uint8_t waves_waveform1[256] PROGMEM = {
  127, 124, 121, 118, 115, 112, 109, 106, 103, 99,  96,  93,  90,  87,  84,
  81,  79,  76,  73,  70,  67,  64,  62,  59,  56,  54,  51,  49,  46,  44,
  42,  39,  37,  35,  33,  31,  29,  27,  25,  23,  21,  19,  18,  16,  15,
  13,  12,  10,  9,   8,   7,   6,   5,   4,   3,   3,   2,   1,   1,   0,
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   2,   3,   3,
  4,   5,   6,   7,   8,   9,   10,  12,  13,  15,  16,  18,  19,  21,  23,
  25,  27,  29,  31,  33,  35,  37,  39,  42,  44,  46,  49,  51,  54,  56,
  59,  62,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99,
  103, 106, 109, 112, 115, 118, 121, 124, 128, 131, 134, 137, 140, 143, 146,
  149, 152, 156, 159, 162, 165, 168, 171, 174, 176, 179, 182, 185, 188, 191,
  193, 196, 199, 201, 204, 206, 209, 211, 213, 216, 218, 220, 222, 224, 226,
  228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 245, 246, 247, 248, 249,
  250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245,
  243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220, 218,
  216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179,
  176, 174, 171, 168, 165, 162, 159, 156, 152, 149, 146, 143, 140, 137, 134,
  131};

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