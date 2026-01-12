/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    SFT_CAPS,
    SPC_G_MO,
    ENT_G_MO,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void sft_finished(tap_dance_state_t *state, void *user_data);
void sft_reset(tap_dance_state_t *state, void *user_data);


void spc_finished(tap_dance_state_t *state, void *user_data);
void spc_reset(tap_dance_state_t *state, void *user_data);


void ent_finished(tap_dance_state_t *state, void *user_data);
void ent_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------------------------.      ,----------------------------------------------------------------------------------.
          QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,         KC_T, MS_WHLU,        KC_VOLU,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,               KC_BSPC,
  //|------------+--------+--------+--------+--------+-------------+--------|      |--------+-------------+--------+--------+--------+--------+-----------------------|
     TD(SFT_CAPS),    KC_A,    KC_S,    KC_D,    KC_F,         KC_G, MS_WHLD,        KC_VOLD,         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, MT(MOD_RSFT, KC_QUOT),
  //|------------+--------+--------+--------+--------+-------------+--------|      |--------+-------------+--------+--------+--------+--------+-----------------------|
          KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,         KC_B,                                  KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  MT(MOD_RCTL, KC_TAB),
  //|------------+--------+--------+--------+--------+-------------+--------|      |--------+-------------+--------+--------+--------+--------+-----------------------|
                                              KC_LALT, TD(SPC_G_MO),    MO(3),          MO(3), TD(ENT_G_MO),   MO(4)
                                          //`-------------------------------'      `-------------------------------'
  ),

    [1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.      ,--------------------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, MS_WHLL,        MS_WHLU,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, MS_ACL2, MS_BTN1,   MS_UP, MS_BTN2, MS_WHLU, MS_WHLR,        MS_WHLD, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______, MS_ACL0, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD,                          KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,        MS_BTN1, MS_BTN2, KC_LALT
                                      //`--------------------------'      `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.      ,-------------------------------------------------------------------------.
      _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), _______,        _______,     S(KC_6),   S(KC_7),    S(KC_8),   S(KC_9), S(KC_0), _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+------------+----------+-----------+----------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______,        _______,     KC_MINS,    KC_EQL, S(KC_BSLS),   KC_LBRC, KC_RBRC,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+------------+----------+-----------+----------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          S(KC_MINUS), S(KC_EQL), S(KC_COMM), S(KC_DOT), KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+------------+----------+-----------+----------+--------+--------|
                                          _______,   MO(5), _______,        _______, _______, _______
                                      //`--------------------------'      `--------------------------'
  ),


    [3] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------------.      ,----------------------------------------------------------------------.
      _______,    G(KC_1), G(KC_2), G(KC_3),    G(KC_4), G(KC_5), _______,        _______, G(KC_6), G(KC_7),    G(KC_8),   G(KC_9),    G(KC_0), _______,
  //|--------+-----------+--------+--------+-----------+--------+--------|      |--------+--------+--------+-----------+----------+-----------+--------|
      _______,    G(KC_Q), G(KC_W), G(KC_G),    G(KC_D), G(KC_E), _______,        _______, G(KC_H), G(KC_J),    G(KC_K),   G(KC_L), G(XXXXXXX), _______,
  //|--------+-----------+--------+--------+-----------+--------+--------|      |--------+--------+--------+-----------+----------+-----------+--------|
      _______, G(XXXXXXX), G(KC_S), G(KC_C), G(XXXXXXX), G(KC_B),                          G(KC_N), G(KC_M), G(KC_COMM), G(KC_DOT), G(KC_SLSH), _______,
  //|--------+-----------+--------+--------+-----------+--------+--------|      |--------+--------+--------+-----------+----------+-----------+--------|
                                          _______, _______, _______,        _______, _______, _______
                                      //`--------------------------'      `--------------------------'
  ),

    [4] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.      ,--------------------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        XXXXXXX,  KC_NUM,   KC_P7,   KC_P8,   KC_P9, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,        XXXXXXX, XXXXXXX,   KC_P4,   KC_P5,   KC_P6, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT,                            KC_P0,   KC_P1,   KC_P2,   KC_P3, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,        _______, _______, _______
                                      //`--------------------------'      `--------------------------'
  ),


    [5] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.      ,--------------------------------------------------------------.
      XXXXXXX, RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,        _______, _______, _______
                                      //`--------------------------'      `--------------------------'
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (!state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

static td_tap_t sft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void sft_finished(tap_dance_state_t *state, void *user_data) {
    sft_tap_state.state = cur_dance(state);
    switch (sft_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LEFT_SHIFT); break;
        case TD_SINGLE_HOLD: register_code(KC_LEFT_SHIFT); break;
        case TD_DOUBLE_TAP: tap_code(KC_CAPS_LOCK); break;
        case TD_DOUBLE_HOLD: register_code(KC_LEFT_SHIFT); break;
        default: break;
    }
}

void sft_reset(tap_dance_state_t *state, void *user_data) {
    switch (sft_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LEFT_SHIFT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LEFT_SHIFT); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LEFT_SHIFT); break;
        default: break;
    }
    sft_tap_state.state = TD_NONE;
}


static td_tap_t spc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void spc_finished(tap_dance_state_t *state, void *user_data) {
    spc_tap_state.state = cur_dance(state);
    switch (spc_tap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_SPACE); break;
        case TD_SINGLE_HOLD: layer_on(1); break;
        case TD_DOUBLE_TAP: tap_code(KC_LGUI); break;
        case TD_DOUBLE_HOLD: register_code(KC_LGUI); break;
        default: break;
    }
}

void spc_reset(tap_dance_state_t *state, void *user_data) {
    switch (spc_tap_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD: layer_off(1); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LGUI); break;
        default: break;
    }
    spc_tap_state.state = TD_NONE;
}

static td_tap_t ent_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ent_finished(tap_dance_state_t *state, void *user_data) {
    ent_tap_state.state = cur_dance(state);
    switch (ent_tap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_ENT); break;
        case TD_SINGLE_HOLD: layer_on(2); break;
        case TD_DOUBLE_TAP: tap_code(KC_LGUI); break;
        case TD_DOUBLE_HOLD: register_code(KC_LGUI); break;
        default: break;
    }
}

void ent_reset(tap_dance_state_t *state, void *user_data) {
    switch (ent_tap_state.state) {
        case TD_SINGLE_TAP: break;
        case TD_SINGLE_HOLD: layer_off(2); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LGUI); break;
        default: break;
    }
    ent_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset),
    [SPC_G_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_finished, spc_reset),
    [ENT_G_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ent_finished, ent_reset)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return TAPPING_TERM - 20;
        default:
            return TAPPING_TERM;
    }
}
