// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "quantum.h"



enum custom_layers {
     _COLEMAK_DH,
     _NAV,
     _SYM,
     _NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_COLEMAK_DH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_HOME,          KC_END,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    SH_OS,   OSL(_NAV), KC_SPC,                  QK_LEAD, KC_ENT,  SH_OS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, KC_VOLU, /* mov tab,ent,bks,esc here*/KC_MNXT, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,
     _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_MUTE,                              KC_MPLY, MS_LEFT, MS_DOWN, MS_UP  , MS_RGHT, _______,
     _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_VOLD, _______,            _______, KC_MPRV, MS_BTN1, MS_BTN2, _______, KC_PSCR, _______,
                                      _______, _______, _______,                     _______, _______, _______
  ),

  [_SYM] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______, _______,
     _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_DLR,                               KC_CIRC, KC_PIPE, KC_AMPR, KC_TILD, KC_GRV,  _______,
     _______, KC_QUOT, KC_LPRN, KC_RPRN, KC_SCLN, KC_COLN,/*rotate & +ent -coln       */KC_AT,   KC_PLUS, KC_EQL,  KC_EXLM, KC_DQT,  _______,
     _______, KC_LT,   KC_GT,   KC_MINS, KC_BSLS, KC_PERC, _______,            _______, KC_HASH, KC_ASTR, KC_UNDS, KC_SLSH, KC_QUES, _______,
                                      _______, _______, _______,                     _______, _______, _______
  ),

  [_NUM] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______, _______,
     _______, _______, KC_7,    KC_8,    KC_9,    _______,                              _______, KC_F1  , KC_F4  , KC_F7  , KC_F10 , _______,
     _______, KC_0   , KC_4,    KC_5,    KC_6,    KC_DOT ,                              _______, KC_F2  , KC_F5  , KC_F8  , KC_F11 , _______,
     _______, _______, KC_1   , KC_2   , KC_3   , KC_COMM, _______,            _______, _______, KC_F3  , KC_F6  , KC_F9  , KC_F12 , _______,
                                      _______, _______, _______,                     _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
            if (record->event.pressed) {
                // 1. Clear physical/standard modifiers
                clear_mods();

                // 2. Clear One-Shot modifiers (if you use them)
                clear_oneshot_mods();

                // 3. Clear any locked layers (optional)
                layer_clear();

                // 4. Send the actual Escape keypress
                register_code(KC_ESC);
            } else {
                unregister_code(KC_ESC);
            }
            return false; // Skip default handling since we handled it manually

        default:
            return true; // Process all other keys normally
    }
}

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_ALT, KC_BSPC, KC_DEL);
const key_override_t shift_comma_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t shift_dot_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &shift_comma_override,
    &shift_dot_override
};

#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Left Half to Right Half
    [0] = {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}}, // Row 0 -> Row 5
    [1] = {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}, // Row 1 -> Row 6
    [2] = {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}}, // Row 2 -> Row 7
    [3] = {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}}, // Row 3 -> Row 8
    [4] = {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}}, // Row 4 -> Row 9

    // Right Half to Left Half
    [5] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}}, // Row 5 -> Row 0
    [6] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}}, // Row 6 -> Row 1
    [7] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}}, // Row 2 -> Row 2
    [8] = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}, // Row 8 -> Row 3
    [9] = {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}}  // Row 9 -> Row 4
};
#endif

void keyboard_post_init_user(void) {
    // Force RGB on and set a high brightness level on startup
    rgb_matrix_enable_noeeprom();
//    rgb_matrix_sethsv_noeeprom(HSV_WHITE);
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return true;
}
#endif



void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_N)) {
        layer_on(_NUM);
    }
}
