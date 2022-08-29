#pragma once
#include <arduino.h>

static uint32_t globalTime = 0;
static byte globalWait = 0;

class Button {
  byte _counter = 0;
  byte _pin;
  bool _direct;
  int _clickTime;
  byte _debounceTime;
  int _holdTime;
  uint32_t _lastTime = 0;
  bool holdFlag = false;
  bool _isHold = false;
  bool _hasWait = false;
  
  
  public: 
  Button(){}; 
  Button(byte pin, bool direct, byte debounceTime = 50, int clickTime = 350, int holdTime = 500);

  void check(byte port);

  bool isClick();
  bool isOnce();
  bool isDouble();
  bool isTriple();
  bool isHold();

  int getCounter();

  bool hasWaitTime(int _time);
  static bool hasWait();
  static void interupts(bool state);
  
  };
