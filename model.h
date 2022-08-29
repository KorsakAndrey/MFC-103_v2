#pragma once
#include <arduino.h>

#define CHANNEL_MAX 16
#define BRIGHT_MAX 7
#define SHIFT_MEMORY 1
#define ITEMS_MENU 9

#define TO_UP true
#define TO_DOWN false
#define COMMAND true
#define PRESET false
#define COMMAND_1 0
#define COMMAND_2 1
#define MUTE 2
#define PRESET_1 0
#define PRESET_2 1


class Model {
  private:
    byte _preset = 0;
    byte _mode = 1;
    byte _menuItem = 0;

    struct {
      bool _sw_1 = false;
      bool _sw_2 = false;
      bool _sw_mute = false;
    } switchs;

    //In memory
    struct {
      byte _channel = 1;
      byte _bright = 3;
      byte _maxPreset = 127;
      bool _auto = false;
      bool _command = true;
      byte _command_1 = 1;
      byte _command_2 = 2;
      byte _command_mute = 3;
      byte _preset_1 = 6;
      byte _preset_2 = 8;
    } memory;

    const byte maxValue[10] = {16, 7, 127, 1, 1, 127, 127, 127, 127, 127};

    void readMemory();

  public:

    Model() {
      readMemory();
    };

    void writeMemory();

    void changePreset(bool direct);
    void changeSwitch(byte switchNum);
    void setPreset(byte preset);
    void setPreset(byte number, byte preset);
    byte getPreset(byte number);
    bool getSwitch(byte switchNum);
    byte getMaxPreset();
    byte getPreset();

    void setMode(byte mode);
    byte getMode();

    void changeChannel(bool direct);
    byte getChannel();

    void changeBright(bool direct);
    byte getBright();

    void setAuto(bool state);
    bool getAuto();

    void setCommand(bool state);
    void setCommand(byte number, byte command);
    byte getCommand(byte number);
    bool getCommand();

    void changeValue(bool direct, byte item);
    void changeItem(bool direct);
    byte getItem();
};
