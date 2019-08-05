#include "Arduino.h"
#include <ProTrinketHidCombo.h>
#include "keypad_state.h"

KeyPadAppState::KeyPadAppState(KeyPadStateDefinition **stateDefinitions, uint8_t numdefinitions, UartComm *uart_comm_in){
  keypadStateDefinitions = stateDefinitions;
  numKeypadStateDefinitions = numdefinitions;
  uart_comm = uart_comm_in;
};

void KeyPadAppState::processAction(KeyPadAction action){
  if (action.action == STATE_ACTION_MULTIMEDIA_KEY){
    TrinketHidCombo.pressMultimediaKey(action.param1);
  }
  if (action.action == STATE_ACTION_KEYPRESS_RELEASE || action.action == STATE_ACTION_KEYPRESS){
    TrinketHidCombo.pressKey(action.param2, action.param1);
  }
  if (action.action == STATE_ACTION_KEYRELEASE || action.action == STATE_ACTION_KEYPRESS_RELEASE){
    TrinketHidCombo.pressKey(0, 0);
  }
}
void KeyPadAppState::processStateEvent(KeyPadEvent event){
  // rotary 1
  if (event.rotary1 == ROTARY_CW_EVENT){
    processAction(keypadStateDefinitions[currentKeypadStateDefinition]->rotary1_cw);
  }else if (event.rotary1 == ROTARY_CCW_EVENT){
    processAction(keypadStateDefinitions[currentKeypadStateDefinition]->rotary1_ccw);
  }
  // rotary 2
  if (event.rotary2 == ROTARY_CW_EVENT){
    processAction(keypadStateDefinitions[currentKeypadStateDefinition]->rotary2_cw);
  }else if (event.rotary2 == ROTARY_CCW_EVENT){
    processAction(keypadStateDefinitions[currentKeypadStateDefinition]->rotary2_ccw);
  }

  for (int i=0; i<8; i++){
    if (event.button[i] == KEY_PRESSED_EVENT){
      processAction(keypadStateDefinitions[currentKeypadStateDefinition]->button_actions_keypress[i]);
    }else if(event.button[i] == KEY_RELEASED_EVENT){
      processAction(keypadStateDefinitions[currentKeypadStateDefinition]->button_actions_release[i]);
    }
  }
}