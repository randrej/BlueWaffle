#include "Setting.h"

void _setting_increment(SettingUint8 *s)
{
  if (*(s->dataAddress) < s->upperLimit)
  {
    *(s->dataAddress) += 1;
  }
}

void _setting_decrement(SettingUint8 *s)
{
  if (*(s->dataAddress) > s->lowerLimit)
  {
    *(s->dataAddress) -= 1;
  }
}

void _setting_incrementUint16(SettingUint16 *s)
{
  if (*(s->dataAddress) < s->upperLimit)
  {
    *(s->dataAddress) += 1;
  }
}

void _setting_decrementUint16(SettingUint16 *s)
{
  if (*(s->dataAddress) > s->lowerLimit)
  {
    *(s->dataAddress) -= 1;
  }
}

void _setting_displayDirect(SettingUint8 *s)
{
  _lcd_setCursor(s->displCoordX, s->displCoordY);
  _lcd_putuintc(*(s->dataAddress), s->len);
}

void _setting_displayPlusOne(SettingUint8 *s)
{
  _lcd_setCursor(s->displCoordX, s->displCoordY);
  _lcd_putuintc(*(s->dataAddress) + 1, s->len);
}

void _setting_displayYesNo(SettingUint8 *s)
{
  _lcd_setCursor(s->displCoordX, s->displCoordY);
  if (*(s->dataAddress))
  {
    _lcd_puts_p(_text_config_yes);
  }
  else
  {
    _lcd_puts_p(_text_config_no);
  }
}

void _setting_displayDirectUint16(SettingUint16 *s)
{
  _lcd_setCursor(s->displCoordX, s->displCoordY);
  _lcd_putuintc(*(s->dataAddress), s->len);
}

void _setting_displayPlusOneUint16(SettingUint16 *s)
{
  _lcd_setCursor(s->displCoordX, s->displCoordY);
  _lcd_putuintc(*(s->dataAddress) + 1, s->len);
}

void _setting_displayYesNoUint16(SettingUint16 *s)
{
  _lcd_setCursor(s->displCoordX, s->displCoordY);
  if (*(s->dataAddress))
  {
    _lcd_puts_p(_text_config_yes);
  }
  else
  {
    _lcd_puts_p(_text_config_no);
  }
}
