#pragma once
#include "model.h"
#include "intbtn.h"
#include "powercontrol.h"



class Controller {
  private:
  Button _up;
  Button _down;
  Button _mid;
  Model* _model;
  PowerControl* _power;

  bool _viewUpdate = true;
  bool _switchUpdate = false;
  bool _send = false;
  bool _hasSend = false;
  bool _menuEdit = false;

  bool changeFunction(void (Model::* function)(bool), Model& model);

  public:
  Controller(byte pinUp, byte pinDown, byte pinMid, Model* model, PowerControl* power);

  void checkButtons(byte state);
  void interupt(bool state);
  void action();
  bool hasUpdate();
  bool hasWait();
  void view();

  };
