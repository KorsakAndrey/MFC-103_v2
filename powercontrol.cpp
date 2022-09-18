#include "powercontrol.h"

#define VREF 1.1
/*((DIV_R1 + DIV_R2) / DIV_R2) = 4.6
  DIV_R1 9750  betwen "+" and POWER_SENS
  DIV_R2 2700  betwen "-" and POWER_SENS
*/
#define POWER_COEFF 4.6

PowerControl::PowerControl(byte powerPin, byte powerSens, double lowBat) {
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin , HIGH);

  _powerPin = powerPin;
  _powerSens = powerSens;
  _lowBat = lowBat;

  //Set VREF 1.1v
  analogReference(INTERNAL);
  check();
}

void PowerControl::poweroff() {
  digitalWrite(_powerPin, LOW);
}

void PowerControl::check() {
  double temp = (double)analogRead(_powerSens) * VREF * POWER_COEFF / 1024;
  _voltage = (float)temp;
}

float PowerControl::getVoltage() {
  check();
  return _voltage;
}

bool PowerControl::hasLow() {
  check();
  
  if (!_lowFlag) {
    _lowFlag = _voltage < _lowBat;
  } else {
    _lowFlag = !(_voltage > (_lowBat + 0.1));
  }

  return _lowFlag;
}
