#pragma once

static bool portInts[] = {false, false, false};

void setPinIn(byte pin_) {
  byte port = pin_ / 8;
  byte pin =  pin_ % 8;

  switch(port) {
    //Port D pcint_2
    case 0:{
        PORTD |= 1 << pin;
        DDRD &= !(1 << pin);
        PCMSK2 |= 1 << pin;
        portInts[2] = true;
        break;
      }
      
    //Port B pcint_0
    case 1: {
        PORTB |= 1 << pin;
        DDRB &= !(1 << pin);
        PCMSK0 |= 1 << pin;
        portInts[0] = true;
        break;
      }
    
    //Port C pcint_1
    case 2: {
        PORTC |= 1 << pin;
        DDRC &= !(1 << pin);
        PCMSK1 |= 1 << pin;
        portInts[3] = true;
        break;
      }
    }
  }

  void portsInt(bool state){
    for(byte i = 0; i < (sizeof(portInts) / sizeof(portInts[0])); i++) {
      if(state) {
          if(portInts[i]){
            PCICR |= 1 << i;
          }
        } else {
          if(portInts[i]){
            PCICR = 0;
          }
        }
      }
    }
