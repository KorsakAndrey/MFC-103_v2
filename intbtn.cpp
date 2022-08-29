#include "intbtn.h"
#include "portconfig.h"

Button::Button(byte pin, bool direct, byte debounceTime, int clickTime, int holdTime) {
  _pin = pin % 8;
  _direct = direct;
  _debounceTime = debounceTime;
  _clickTime = clickTime;
  _holdTime = holdTime;
  setPinIn(pin);
}

void Button::check(byte port) {
  uint32_t curentTime = millis();
  if ((holdFlag = !((port >> _pin) & !_direct)) && (curentTime - _lastTime > _debounceTime)) {
    _isHold = holdFlag;
    _hasWait = true;
    if (curentTime - _lastTime < _clickTime && _counter != 0) {
      _counter++;
    } else {
      _counter = 1;
    }
    globalTime = _lastTime = curentTime;
    globalWait++;
  }
}

bool Button::isClick() {
  if (_counter != 0) {
    _counter = 0;
    globalTime -= _clickTime;
    globalWait--;
    return true;
  }
  return false;
}

bool Button::isOnce() {
  if (_counter == 1 && !hasWaitTime(_clickTime)) {
    _counter = 0;
    _hasWait = false;
    globalWait--;
    return true;
  }
  return false;
}

bool Button::isDouble() {
  if (_counter == 2 && !hasWaitTime(_clickTime)) {
    _counter = 0;
    _hasWait = false;
    globalWait--;
    return true;
  }
  return false;
}

bool Button::isTriple() {
  if (_counter == 3 && !hasWaitTime(_clickTime)) {
    _counter = 0;
    _hasWait = false;
    globalWait--;
    return true;
  }
  return false;
}

bool Button::isHold() {
  if (_isHold && !hasWaitTime(_holdTime)) {
    _isHold = false;
    _counter = 0;
    _hasWait = false;
    globalWait--;
    return holdFlag;
  }
  return false;
}

int Button::getCounter() {
  return _counter;
}

bool Button::hasWaitTime(int _time) {
  return millis() - _lastTime <= _time;
}

static bool Button::hasWait() {
  return globalWait == 0 ? false : true;
}

static void Button::interupts(bool state) {
  portsInt(state);
};
