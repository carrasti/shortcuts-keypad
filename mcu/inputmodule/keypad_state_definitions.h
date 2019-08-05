/*
 * Keypad state
 */

#ifndef keypad_state_definitions_h
#define keypad_state_definitions_h

#define NUM_KEYPAD_STATES 3


KeyPadStateDefinition initial_state = {
  .id = 0,
  .rotary1_cw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = 48, .param2 = KEYCODE_MOD_LEFT_CONTROL},
  .rotary1_ccw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = 56, .param2 = KEYCODE_MOD_LEFT_CONTROL},
  .rotary2_cw = {.action = STATE_ACTION_MULTIMEDIA_KEY, .param1 = MMKEY_VOL_UP},
  .rotary2_ccw = {.action = STATE_ACTION_MULTIMEDIA_KEY, .param1 = MMKEY_VOL_DOWN}
};

KeyPadStateDefinition gimp1 = {
  .id = 1,
  .rotary1_cw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = 48},
  .rotary1_ccw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = 56},
  .rotary2_cw = {.action = STATE_ACTION_MULTIMEDIA_KEY, .param1 = MMKEY_VOL_UP},
  .rotary2_ccw = {.action = STATE_ACTION_MULTIMEDIA_KEY, .param1 = MMKEY_VOL_DOWN}
};

KeyPadStateDefinition gthumb = {
  .id = 2,
  .rotary1_cw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_SQBRAK_RIGHT, .param2 = KEYCODE_MOD_RIGHT_ALT},
  .rotary1_ccw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_SQBRAK_LEFT, .param2 = KEYCODE_MOD_RIGHT_ALT},
  .rotary2_cw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_PAGE_DOWN},
  .rotary2_ccw = {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_PAGE_UP},
  .button_actions_keypress = {
      {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_PAGE_UP},
      {},
      {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_PAGE_DOWN},
      {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_SQBRAK_LEFT, .param2 = KEYCODE_MOD_RIGHT_ALT},
      {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_DELETE},
      {.action = STATE_ACTION_KEYPRESS_RELEASE, .param1 = KEYCODE_SQBRAK_RIGHT, .param2 = KEYCODE_MOD_RIGHT_ALT},
      {},
      {}
  }
};


KeyPadStateDefinition *state_definitions[NUM_KEYPAD_STATES] = {
  &gthumb,
  &initial_state,
  &gimp1
};


#endif