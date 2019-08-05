/*
 * Rotary encoder library for Arduino.
 */

#include "debounced_input.h"

DebouncedInput::DebouncedInput(int pin_in, int pin_mode_in, unsigned long debounceInterval_in, boolean negate_in) {
  pin = pin_in;
  pinMode(pin, pin_mode_in); 
  debounceInterval = debounceInterval_in;
  negate = negate_in;
  value = dv();
}

boolean DebouncedInput::dv(){
  boolean n = negate ? ! digitalRead(pin) : digitalRead(pin);
  return n;
}

boolean DebouncedInput::readValue(){
  unsigned long currentMillis = millis();
  boolean new_value = dv();

  if ((new_value != value) && (currentMillis - lastRead >= debounceInterval)){
    value = new_value;
    lastRead = currentMillis;
  }
  return value;
}