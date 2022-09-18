#pragma once


//Model is full complete (maybe not(! )
//Controller is half complete
//Viewer don't complete
/*TODO LIST
   Buttons - complete
   Change Programm - complete
   Change Command - complete
   Settings menu - complete(without exit and voltage controll)
   PowerControl - complete(i'm think...)

    View controller

    Send MIDI
*/

#define TEST

#define UP 8
#define DOWN 9
#define MID 10

#define CLICK_TIME 350
#define DEBOUNCE_TIME 50

#define POWER_PIN 7
#define POWER_SENS A3
#define POWER_LOW 3.60

#include <avr/sleep.h>
#include "model.h"
#include "controller.h"
#include "powercontrol.h"

PowerControl power = PowerControl(POWER_PIN, POWER_SENS, POWER_LOW);
Model model = Model();
Controller controller = Controller(UP, DOWN, MID, &model, &power);

void setup() {
#ifdef TEST
  Serial.begin(9600);
#else
  Serial.begin(31250);
#endif
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  controller.interupt(true); //Enable interupt
}

ISR(PCINT0_vect) { //For port B
  controller.interupt(false); //Disable interupt
#ifdef TEST
  Serial.println("\nInterupt");
  Serial.flush();
#endif
  controller.checkButtons(PINB);
  controller.interupt(true); //Enable interupt
}

void loop() {

  if (!controller.hasWait()) {
#ifdef TEST
    Serial.print("\nGo to sleep");
    Serial.flush();
#endif
    sleep_enable();
    sleep_mode();
    sleep_disable();
#ifdef TEST
    Serial.print("\nAvake");
    Serial.flush();
#endif
  }

  controller.action();

  if (controller.hasUpdate()) {
    controller.view();
  }

}
