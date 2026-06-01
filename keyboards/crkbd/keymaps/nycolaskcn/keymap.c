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

#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include "modifiers.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
// Se o console estiver habilitado, o macro chama a função
#    define debug(str) uprintf(str)
#else
// Se não estiver, o macro é substituído por um espaço vazio
#    define debug(str)
#endif

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
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    G_MO,
};

td_state_t cur_dance(tap_dance_state_t *state);

void gui_finished(tap_dance_state_t *state, void *user_data);
void gui_reset(tap_dance_state_t *state, void *user_data);

// Layers enum
enum { BASE = 0, GAMING, NUM_MOUSE, G_NUMS, SIMBOLS, HYPR, FNK_NPAD, CONTROL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_F4, KC_VOLU, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        //-----------------------------------------------------------------------------------------------------------------||
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_F5, KC_VOLD, KC_H, KC_J, KC_K, KC_L, KC_SCLN, MT(MOD_RSFT, KC_QUOT),
        //-----------------------------------------------------------------------------------------------------------------||
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RCTL, KC_TAB),
        //-----------------------------------------------------------------------------------------------------------------||
        KC_LALT, LT(NUM_MOUSE, KC_SPC), TD(G_MO), TD(G_MO), LT(SIMBOLS, KC_ENT), MO(FNK_NPAD)
        //-----------------------------------------------------------------------------------------------------------------||
        ),

    [GAMING] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_F3, KC_VOLU, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        //-----------------------------------------------------------------------------------------------------------------||
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_F5, KC_VOLD, KC_H, KC_J, KC_K, KC_L, KC_SCLN, MT(MOD_RSFT, KC_QUOT),
        //-----------------------------------------------------------------------------------------------------------------||
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TAB,
        //-----------------------------------------------------------------------------------------------------------------||
        KC_LALT, KC_SPC, MO(G_NUMS), TD(G_MO), LT(SIMBOLS, KC_ENT), MO(FNK_NPAD)
        //-----------------------------------------------------------------------------------------------------------------||
        ),
    [NUM_MOUSE] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, MS_WHLL, MS_WHLU, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, MS_ACL2, MS_BTN1, MS_UP, MS_BTN2, MS_WHLU, MS_WHLR, MS_WHLD, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_CAPS, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, MS_ACL0, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_DEL, KC_LALT,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, _______, _______, MS_BTN1, MS_BTN2, MS_BTN3
        //-----------------------------------------------------------------------------------------------------------------||
        ),
    [G_NUMS] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, XXXXXXX, MS_WHLU, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, KC_6, KC_7, KC_8, KC_9, KC_0, XXXXXXX, MS_WHLD, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_CAPS, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_DEL, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
        //-----------------------------------------------------------------------------------------------------------------||
        ),

    [SIMBOLS] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), _______, _______, S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, _______, KC_EQL, KC_MINS, S(KC_BSLS), KC_LBRC, KC_RBRC, KC_GRV,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, XXXXXXX, XXXXXXX, ALGR(KC_COMM), XXXXXXX, XXXXXXX, S(KC_EQL), S(KC_MINS), S(KC_COMM), S(KC_DOT), KC_BSLS, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, MO(CONTROL), _______, _______, _______, _______
        //-----------------------------------------------------------------------------------------------------------------||
        ),

    [HYPR] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        _______, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5), _______, _______, G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0), _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, G(KC_Q), G(KC_W), G(KC_D), G(KC_G), G(KC_E), _______, _______, G(KC_H), G(KC_J), G(KC_K), G(KC_L), G(KC_SCLN), _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, G(KC_Z), G(KC_S), G(KC_C), G(KC_V), G(KC_B), G(KC_N), G(KC_M), G(KC_COMM), G(KC_DOT), G(KC_SLSH), _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, _______, _______, _______, G(KC_ENT), KC_LALT
        //-----------------------------------------------------------------------------------------------------------------||
        ),

    [FNK_NPAD] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, XXXXXXX, KC_NUM, KC_P7, KC_P8, KC_P9, KC_P0, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX, XXXXXXX, KC_P4, KC_P5, KC_P6, KC_COMM, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_P0, KC_P1, KC_P2, KC_P3, KC_DOT, _______,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, _______, _______, _______, _______, _______
        //-----------------------------------------------------------------------------------------------------------------||
        ),

    [CONTROL] = LAYOUT_split_3x6_3_ex2(
        //-----------------------------------------------------------------------------------------------------------------||
        XXXXXXX, RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG, XXXXXXX, XXXXXXX, TG(GAMING), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //-----------------------------------------------------------------------------------------------------------------||
        XXXXXXX, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //-----------------------------------------------------------------------------------------------------------------||
        XXXXXXX, RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //-----------------------------------------------------------------------------------------------------------------||
        _______, _______, _______, _______, _______, _______
        //-----------------------------------------------------------------------------------------------------------------||
        )};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [1] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [2] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [3] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
};
#endif

// ================================= State indicator
bool is_a_valid_led(uint8_t led_index, uint8_t led_min, uint8_t led_max) {
    return led_index >= led_min && led_index < led_max && led_index != NO_LED;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    hsv_t hsv;
    switch (layer) {
        case NUM_MOUSE:
            hsv = (hsv_t){217, 131, 255};
            break;
        case SIMBOLS:
            hsv = (hsv_t){143, 147, 255};
            break;
        case HYPR:
            hsv = (hsv_t){103, 144, 255};
            break;
        case FNK_NPAD:
            hsv = (hsv_t){26, 187, 255};
            break;
        case CONTROL:
            hsv = (hsv_t){252, 217, 255};
            break;
        case GAMING:
            hsv = (hsv_t){186, 213, 255};
            break;
        default:
            hsv = (hsv_t){252, 217, 255};
            break;
    };

    hsv.v     = rgb_matrix_get_val();
    rgb_t rgb = hsv_to_rgb(hsv);

    // layer
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (is_a_valid_led(index, led_min, led_max) && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                }
            }
        }
    }

    // capslock indicator
    if (host_keyboard_led_state().caps_lock) {
        uint8_t index_r = g_led_config.matrix_co[7][4];
        RGB_MATRIX_INDICATOR_SET_COLOR(index_r, rgb.r, rgb.g, rgb.b);
    }

    return false;
}
// ================================= Keys overrides
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_ALT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &delete_key_override,
};

// ================================= Custom process record user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool alt_as_shift_active = false;
    static bool alt_as_ctrl_active  = false;

    switch (keycode) {
        case KC_LALT:
            if (record->event.pressed) {
                uint8_t mods = get_mods();

                if ((mods & MOD_BIT(KC_LCTL)) || (mods & MOD_BIT(KC_RCTL))) {
                    alt_as_shift_active = true;
                    register_code(KC_LSFT);
                    return false;
                }

                if ((mods & MOD_BIT(KC_LSFT)) || (mods & MOD_BIT(KC_RSFT))) {
                    alt_as_ctrl_active = true;
                    register_code(KC_LCTL);
                    return false;
                }
            } else {
                if (alt_as_shift_active) {
                    alt_as_shift_active = false;
                    unregister_code(KC_LSFT);
                    return false;
                }
                if (alt_as_ctrl_active) {
                    alt_as_ctrl_active = false;
                    unregister_code(KC_LCTL);
                    return false;
                }
            }
            break;
    }
    return true;
}

// ================================= Tap dance

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
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (!state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

static td_tap_t gui_tap_state = {.is_press_action = true, .state = TD_NONE};

void gui_finished(tap_dance_state_t *state, void *user_data) {
    gui_tap_state.state = cur_dance(state);
    switch (gui_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LGUI);
            break;
        case TD_SINGLE_HOLD:
            debug("Enable HYPR");
            layer_on(HYPR);
            register_mods(MOD_LGUI);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LGUI);
            break;
        default:
            break;
    }
}

void gui_reset(tap_dance_state_t *state, void *user_data) {
    switch (gui_tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            debug("RESETING Hypr");
            layer_off(HYPR);
            unregister_mods(MOD_LGUI);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            break;
        default:
            break;
    }
    gui_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {[G_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_finished, gui_reset)};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(G_MO):
            return TAPPING_TERM - 110;
        case LT(SIMBOLS, KC_ENT):
            return TAPPING_TERM - 90;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(SIMBOLS, KC_ENT):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
