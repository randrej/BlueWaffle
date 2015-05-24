#ifndef SETTING_H
#define SETTING_H

#include <avr/io.h>
#include <inttypes.h>
#include <avr/eeprom.h>

#include "AvrMacroLibrary.h"
#include "SettingsAndDimensions.h"
#include "PresetManager.h"
#include "ProgmemText.h"
#include "LcdDisplay.h"

#define ENUM_BUTTON_RIGHT_UP 0
#define ENUM_BUTTON_RIGHT_DN 1
#define ENUM_BUTTON_LEFT_UP 2
#define ENUM_BUTTON_LEFT_DN 3

typedef struct __settingDefinitionUint8
{
  uint8_t *dataAddress;
  uint8_t lowerLimit;
  uint8_t upperLimit;
  void (*display)(struct __settingDefinitionUint8 *);
  uint8_t displCoordX;
  uint8_t displCoordY;
  uint8_t len;
} SettingUint8;

typedef struct __settingDefinitionUint16
{
  uint16_t *dataAddress;
  uint16_t lowerLimit;
  uint16_t upperLimit;
  void (*display)(struct __settingDefinitionUint16 *);
  uint8_t displCoordX;
  uint8_t displCoordY;
  uint8_t len;
} SettingUint16;

typedef struct __settingsMode
{
  SettingUint8 *setting_left;
  SettingUint8 *setting_right;
  const uint8_t *upperLine;
  const uint8_t *lowerLine;
} SettingsMode;

extern void _setting_increment(SettingUint8 *s);
extern void _setting_decrement(SettingUint8 *s);
extern void _setting_incrementUint16(SettingUint16 *s);
extern void _setting_decrementUint16(SettingUint16 *s);

extern void _setting_displayDirect(SettingUint8 *s);
extern void _setting_displayPlusOne(SettingUint8 *s);
extern void _setting_displayYesNo(SettingUint8 *s);
extern void _setting_displayDirectUint16(SettingUint16 *s);
extern void _setting_displayPlusOneUint16(SettingUint16 *s);
extern void _setting_displayYesNoUint16(SettingUint16 *s);

#endif  // SETTING_H
