
/*
Version 1.0  2015-01-01 Initial Version by Mike Barela
*/
#include <Arduino.h>
#include <ProTrinketHidCombo.h>  // include the Adafruit library
#include <Rotary.h> // include the Rotary encoder library

#include "debounced_input.h"
#include "uart_comm.h"
#include "keypad_state.h"
#include "keypad_state_definitions.h"


#define NUM_BUTTONS_KEYPAD 6
#define NUM_BUTTONS_ROTARY 2
#define NUM_BUTTONS (NUM_BUTTONS_KEYPAD + NUM_BUTTONS_ROTARY)

Rotary rotaryLeft = Rotary(6, 5);
Rotary rotaryRight = Rotary(A4, A5);
DebouncedInput rotaryLeftButton = DebouncedInput(A3, INPUT_PULLUP, 20, true);
DebouncedInput rotaryRightButton = DebouncedInput(8, INPUT_PULLUP, 20, true);

DebouncedInput button1 = DebouncedInput(9, INPUT_PULLUP, 20, true);
DebouncedInput button2 = DebouncedInput(12, INPUT_PULLUP, 20, true);
DebouncedInput button3 = DebouncedInput(A1, INPUT_PULLUP, 20, true);
DebouncedInput button4 = DebouncedInput(11, INPUT_PULLUP, 20, true);
DebouncedInput button5 = DebouncedInput(A0, INPUT_PULLUP, 20, true);
DebouncedInput button6 = DebouncedInput(A2, INPUT_PULLUP, 20, true);

DebouncedInput buttons[NUM_BUTTONS] = {
  // the keypad buttons
  DebouncedInput(9, INPUT_PULLUP, 20, true),
  DebouncedInput(12, INPUT_PULLUP, 20, true),
  DebouncedInput(A1, INPUT_PULLUP, 20, true),
  DebouncedInput(11, INPUT_PULLUP, 20, true),
  DebouncedInput(A0, INPUT_PULLUP, 20, true),
  DebouncedInput(A2, INPUT_PULLUP, 20, true),
  // the rotary encoder buttons
  DebouncedInput(A3, INPUT_PULLUP, 20, true), // left rotary button
  DebouncedInput(8, INPUT_PULLUP, 20, true), // right rotary button
};

UartComm uartcomm = UartComm(&Serial);

struct KeyPadEvent keypad_event;
KeyPadAppState appState = KeyPadAppState(state_definitions, NUM_KEYPAD_STATES, &uartcomm);


void setup()
{
  rotaryLeft.begin(true);
  rotaryRight.begin(true);
  TrinketHidCombo.begin();  // initialize USB keyboard code
  // initialise serial at compatible speed of micropython board
  Serial.begin(115200);
  // send some key release commands (for some reason if not done, 
  // first keystroke is not picked up correctly)
  TrinketHidCombo.pressKey(0, 0);
  TrinketHidCombo.pressKey(0, 0);
}
uint8_t rotaryLeftResult;
uint8_t rotaryRightResult;

void loop()
{
  // poll Trinket in each loop
  TrinketHidCombo.poll();
  
  rotaryLeftResult = rotaryLeft.process();
  rotaryRightResult = rotaryRight.process();
  
  if (rotaryLeftResult && rotaryLeftResult == DIR_CW) {
    keypad_event.rotary1 = ROTARY_CW_EVENT;
  }else if (rotaryLeftResult && rotaryLeftResult == DIR_CCW){
    keypad_event.rotary1 = ROTARY_CCW_EVENT;
  }else{
    keypad_event.rotary1 = ROTARY_NO_EVENT;
  }

  if (rotaryRightResult && rotaryRightResult == DIR_CW) {
    keypad_event.rotary2 = ROTARY_CW_EVENT;
  }else if (rotaryRightResult && rotaryRightResult == DIR_CCW){
    keypad_event.rotary2 = ROTARY_CCW_EVENT;
  }else{
    keypad_event.rotary2 = ROTARY_NO_EVENT;
  }

  for (uint8_t i = 0; i < NUM_BUTTONS; i++){
    if (buttons[i].readValue() != appState.inputState.button[i]){
      appState.inputState.button[i] = !appState.inputState.button[i];
      keypad_event.button[i] = appState.inputState.button[i] ? KEY_PRESSED_EVENT: KEY_RELEASED_EVENT;

    }else{
      keypad_event.button[i] = KEY_NO_EVENT;
    }
  }
  appState.processStateEvent(keypad_event);
}