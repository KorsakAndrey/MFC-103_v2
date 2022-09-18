#pragma once
#include <arduino.h>

class PowerControl {
  private:
    byte _powerPin;
    byte _powerSens;
    double _lowBat;
    bool _lowFlag = false;
    
    float _voltage;

  public:
    PowerControl(byte powerPin, byte powerSens, double lowBat);

    void check();
    float getVoltage();
    bool hasLow();
    
    void poweroff();
};
