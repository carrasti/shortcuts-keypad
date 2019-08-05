/*
 * DebouncedInput
 */

#ifndef Debounced_input_h
#define Debounced_input_h

#include "Arduino.h"

class DebouncedInput {
  public:
    int pin;
    DebouncedInput(int, int, unsigned long, boolean);
    boolean readValue();
  private:
    boolean value;
    boolean negate;
    unsigned long debounceInterval;
    unsigned long lastRead = 0;
    boolean dv();

};

#endif