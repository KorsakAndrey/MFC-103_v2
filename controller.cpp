#include "controller.h"

bool Controller::changeFunction(void (Model::* function)(bool), Model& model) {
  bool flag = false;
  if (_up.isClick()) {
    flag = true;
    _viewUpdate = true;
    (model.*function)(TO_UP);
  }
  if (_down.isClick()) {
    flag = true;
    _viewUpdate = true;
    (model.*function)(TO_DOWN);
  }
  return flag;
}


Controller::Controller(byte pinUp, byte pinDown, byte pinMid, Model* model) {
  _up = Button(pinUp, false);
  _down = Button(pinDown, false);
  _mid = Button(pinMid, false);
  _model = model;
}

void Controller::checkButtons(byte state) {
  _up.check(state);
  _down.check(state);
  _mid.check(state);
}

void Controller::interupt(bool state) {
  Button::interupts(state);
}

void Controller::action() {
  switch (_model->getMode()) {
    case 1: {
        if (_mid.isDouble()) {
          _model->setMode(2);
          _viewUpdate = true;
          return;
        }
        if (_mid.isTriple()) {
          _model->setMode(3);
          _viewUpdate = true;
          return;
        }
        if (changeFunction(&Model::changePreset, *_model)) {
          if (_model->getAuto()) {
            _send = true;
          } else {
            _hasSend = true;
          }
        }
        if (_mid.isHold()) {
          //do mute
          _viewUpdate = true;
          _model->changeSwitch(MUTE);
         
        }
      }
      break;

    case 2: {
        if (_mid.isDouble()) {
          _model->setMode(1);
          _viewUpdate = true;
          return;
        }
        //Change command or programm
        if (_model->getCommand()) {
          if (_up.isClick()) {
            _viewUpdate = true;
            _switchUpdate = true;
            _model->changeSwitch(COMMAND_2);
          }
          if (_down.isClick()) {
            _viewUpdate = true;
            _switchUpdate = true;
            _model->changeSwitch(COMMAND_1);
          }
        } else {
          if (_up.isClick()) {
            _viewUpdate = true;
            _send = true;
            _model->setPreset(_model->getPreset(PRESET_2));
          }
          if (_down.isClick()) {
            _viewUpdate = true;
            _send = true;
            _model->setPreset(_model->getPreset(PRESET_1));
          }
        }
      }
      break;

    case 3: {
        if (_mid.isOnce()) {
          if (_menuEdit) {
            _viewUpdate = true;
            _menuEdit = false;
            _model->writeMemory();
          } else {
            _viewUpdate = true;
            _menuEdit = true;
          }
        }
        if (_mid.isTriple()) {
          _model->setMode(1);
          _viewUpdate = true;
          _menuEdit = false;
          return;
        }
        if (_menuEdit) {
          if (_up.isClick()) {
            _viewUpdate = true;
            _model->changeValue(TO_UP, _model->getItem());
          }
          if (_down.isClick()) {
            _viewUpdate = true;
            _model->changeValue(TO_DOWN, _model->getItem());
          }
        } else {
          changeFunction(&Model::changeItem, *_model);
        }
      }
      break;

  }
}

bool Controller::hasUpdate() {
  if (_viewUpdate) {
    _viewUpdate = false;
    return true;
  }
  return false;
}

bool Controller::hasWait(){
  return Button::hasWait();
  }

void Controller::view() {
  Serial.print("\nMode: ");
  Serial.print(_model->getMode());
  if (_model->getMode() == 1) {
    if (_model->getSwitch(MUTE)) {
      Serial.print("\nMUTE");
    } else {
      Serial.print("\nPreset: ");
      Serial.print(_model->getPreset());
    }
    Serial.flush();
  }
  if (_model->getMode() == 2) {
    Serial.print("\nIn process ");
    Serial.flush();
  }
  if (_model->getMode() == 3) {
    Serial.print("\nMENU_ITEM : ");
    Serial.print(_model->getItem());
    Serial.print("\nEDIT : ");
    Serial.print(_menuEdit ? "TRUE" : "FALSE");
    Serial.print("\nChannel: ");
    Serial.print(_model->getChannel());
    Serial.print("\nBright: ");
    Serial.print(_model->getBright());
    Serial.print("\nMax preset: ");
    Serial.print(_model->getMaxPreset());
    Serial.print("\nAutosend: ");
    Serial.print(_model->getAuto());
    Serial.print("\nChannel: ");
    Serial.print(_model->getChannel());
    Serial.flush();
  }

}
