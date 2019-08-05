/*
 * Keypad state
 */

#ifndef keypad_state_h
#define keypad_state_h

#include "Arduino.h"
#include <ProTrinketHidCombo.h> 
#include "uart_comm.h"


#define KEY_NO_EVENT 0x00
#define KEY_PRESSED_EVENT 0x01
#define KEY_RELEASED_EVENT 0x02
#define ROTARY_NO_EVENT 0x00
#define ROTARY_CW_EVENT 0x01
#define ROTARY_CCW_EVENT 0x02

typedef struct KeyPadEvent {
  uint8_t rotary1 = ROTARY_NO_EVENT;
  uint8_t rotary2 = ROTARY_NO_EVENT;

  uint8_t button[8] = {
    KEY_NO_EVENT,
    KEY_NO_EVENT,
    KEY_NO_EVENT,
    KEY_NO_EVENT,
    KEY_NO_EVENT,
    KEY_NO_EVENT,
    KEY_NO_EVENT,
    KEY_NO_EVENT
  };
};

#define STATE_ACTION_CHANGE 0x01  // change state
#define STATE_ACTION_KEYPRESS_RELEASE 0x02  // keypress and release immediately
#define STATE_ACTION_KEYPRESS 0x03 // hold key up
#define STATE_ACTION_KEYRELEASE 0x04 // release
#define STATE_ACTION_MULTIMEDIA_KEY 0x05 // release

typedef struct KeyPadAction {
  uint8_t action;
  uint16_t param1;
  uint16_t param2;
};

typedef struct KeyPadStateDefinition {
  uint8_t id;
  KeyPadAction rotary1_cw;
  KeyPadAction rotary1_ccw;
  KeyPadAction rotary2_cw;
  KeyPadAction rotary2_ccw;
  KeyPadAction button_actions_keypress[8];
  KeyPadAction button_actions_release[8];
};


typedef struct KeyPadState {
  int rotary1 = 0;
  int rotary2 = 0;

  boolean button[8] = {
    false, false, false, false, false, false, false, false
  };
};


class KeyPadAppState {
  public:
    KeyPadState inputState;
    
    KeyPadAppState(KeyPadStateDefinition **, uint8_t, UartComm *);
    void processAction(KeyPadAction);
    void processStateEvent(KeyPadEvent);
  private:
    KeyPadStateDefinition **keypadStateDefinitions; 
    UartComm *uart_comm;
    uint8_t currentKeypadStateDefinition = 0;
    uint8_t numKeypadStateDefinitions;
};

extern KeyPadStateDefinition state_definition0;

#endif