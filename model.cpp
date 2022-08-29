#include <EEPROM.h>
#include "model.h"

void Model::readMemory() {
  EEPROM.get(SHIFT_MEMORY, memory);
}

void Model::writeMemory() {
  EEPROM.put(SHIFT_MEMORY, memory);
}

/*========PRESET========*/
void Model::changePreset(bool direct) {
  if (direct) {
    _preset == memory._maxPreset ? _preset = 0 : _preset++;
  } else {
    _preset == 0 ? _preset = memory._maxPreset : _preset--;
  }
}

void Model::changeSwitch(byte switchNum) {
  bool* pointer = &switchs._sw_1 + switchNum;
  *pointer ? *pointer = 0 :  *pointer = 1;
}

void Model::setPreset(byte preset) {
  _preset = preset;
}

void Model::setPreset(byte number, byte preset) {
  *(&memory._preset_1 + number) = preset;
}

byte Model::getPreset(byte number) {
  return *(&memory._preset_1 + number);
}

bool Model::getSwitch(byte switchNum) {
  bool* pointer = &switchs._sw_1 + switchNum;
  return *pointer;
}

byte Model::getMaxPreset() {
  return memory._maxPreset;
}

byte Model::getPreset() {
  return _preset;
}

/*========MODE========*/
void Model::setMode(byte mode) {
  _mode = mode;
}

byte Model::getMode() {
  return _mode;
}

/*========CHANNEL========*/
void Model::changeChannel(bool direct) {
  if (direct) {
    memory._channel == CHANNEL_MAX ? memory._channel = 0 : memory._channel++;
  } else {
    memory._channel == 0 ? memory._channel = CHANNEL_MAX : memory._channel--;
  }
}

byte Model::getChannel() {
  return memory._channel;
}

/*========BRIGHT========*/
void Model::changeBright(bool direct) {
  if (direct) {
    memory._bright == BRIGHT_MAX ? memory._bright = 0 : memory._bright++;
  } else {
    memory._bright == 0 ? memory._bright = BRIGHT_MAX : memory._bright--;
  }
}

byte Model::getBright() {
  return memory._bright;
}

/*========AUTOSEND========*/
void Model::setAuto(bool state) {
  memory._auto = state;
}

bool Model::getAuto() {
  return memory._auto;
}

/*========COMMAND_CONTROL========*/
void Model::setCommand(bool state) {
  memory._command = state;
}

void Model::setCommand(byte number, byte command) {
  *(&memory._command_1 + number) = command;
}

byte Model::getCommand(byte number) {
  return *(&memory._command_1 + number);
}

bool Model::getCommand() {
  return memory._command;
}

/*========MENU_ITEM========*/
void Model::changeValue(bool direct, byte item) {
  byte* pointer = &memory._channel + item;
  if (direct) {
    *pointer < maxValue[item] ? (*pointer)++ : *pointer = 0;
  } else {
    *pointer > 0 ? (*pointer)-- : *pointer = maxValue[item];
  }
}

void Model::changeItem(bool direct) {
  if (direct) {
    _menuItem < ITEMS_MENU ? _menuItem++ : _menuItem = 0;
  } else {
    _menuItem > 0 ? _menuItem-- : _menuItem = ITEMS_MENU;
  }
}

byte Model::getItem() {
  return _menuItem;
}
