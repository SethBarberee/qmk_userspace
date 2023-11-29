/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "sethbarberee.h"

enum keymap_layers {
    BASE,  // default layer
    SYMB = _LOWER,  // symbols
    MDIA = _RAISE,  // media keys
};

enum custom_keycodes {
  RGB_SLD = USER_SAFE_RANGE,
};

// clang-format off
#define LAYOUT_moonlander_wrapper(...) LAYOUT_moonlander(__VA_ARGS__)

#define LAYOUT_moonlander_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
    ) \
    LAYOUT_moonlander_wrapper( \
        KC_ECAP,  ________________NUMBER_LEFT________________,          KC_LEFT,         KC_RGHT, ________________NUMBER_RIGHT_______________, KC_MINS, \
        KC_TAB,           K01,     K02,     K03,     K04,     K05,     TG(SYMB),         TG(SYMB), K06,     K07,     K08,     K09,     K0A,     KC_BSLS, \
        LT(SYMB, KC_GRV), K11,     K12,     K13,     K14,     K15,      KC_HYPR,           KC_MEH, K16,     K17,     K18,     K19,     LT(MDIA,K1A),     LGUI_T(K1B), \
        KC_LSFT, CTL_T(K21), K22,  K23,     K24,     K25,                                 K26,     K27,     K28,     K29,  RCTL_T(K2A),KC_RSFT, \
        KC_LCTL, LT(SYMB, KC_GRV),  KC_TAB,KC_TAB, KC_TAB,          LALT_T(KC_HOME),        RCTL_T(KC_END), _______, KC_UP, KC_LEFT,   KC_DOWN, KC_RGHT, \
                                            KC_TAB,  KC_SPC, KC_PGUP,                       KC_PGDN, KC_BSPC, KC_ENT \
    )

#define LAYOUT_base_wrapper(...) LAYOUT_moonlander_base(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [SYMB] = LAYOUT_moonlander_wrapper(
        KC_VRSN,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______,  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,           _______, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        _______,  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,           _______, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
        _______,  _______, _______, _______, _______,          RGB_MOD,           RGB_TOG,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                    RGB_VAD, RGB_VAI, TOGGLE_LAYER_COLOR,       RGB_SLD,        RGB_HUD,        RGB_HUI

    ),

    [MDIA] = LAYOUT_moonlander_wrapper(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, KC_WWW_BACK
    ),
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    }
    return true;
}

// TODO do spotify controls
// maybe should create some constants to make this cleaner
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    if (layer_state_is(MDIA)) {
        //RGB_MATRIX_INDICATOR_SET_COLOR(11 , 0x00, 0xFF, 0x00);  // W
        RGB_MATRIX_INDICATOR_SET_COLOR(16, 0x00, 0xFF, 0xFF);  // E
        //RGB_MATRIX_INDICATOR_SET_COLOR(21, 0xFF, 0x00, 0x00);  // R
        //RGB_MATRIX_INDICATOR_SET_COLOR(26, 0xFF, 0x80, 0x00);  // T
        RGB_MATRIX_INDICATOR_SET_COLOR(12 , 0x00, 0xFF, 0xFF);  // S
        RGB_MATRIX_INDICATOR_SET_COLOR(17, 0x00, 0xFF, 0xFF);  // D
        RGB_MATRIX_INDICATOR_SET_COLOR(22, 0x00, 0xFF, 0xFF);  // F
        //RGB_MATRIX_INDICATOR_SET_COLOR(27, 0x7A, 0x00, 0xFF);  // G

        RGB_MATRIX_INDICATOR_SET_COLOR(39, 0x00, 0xFF, 0x00); // MPLY
        RGB_MATRIX_INDICATOR_SET_COLOR(49, 0x00, 0xFF, 0x00); // MNXT
        RGB_MATRIX_INDICATOR_SET_COLOR(54, 0x00, 0xFF, 0x00); // MPRV
        RGB_MATRIX_INDICATOR_SET_COLOR(60, 0xFF, 0x80, 0x00);  // VOLU
        RGB_MATRIX_INDICATOR_SET_COLOR(55, 0xFF, 0x80, 0x00);  // VOLD
        RGB_MATRIX_INDICATOR_SET_COLOR(50, 0xFF, 0x80, 0x00);  // MUTE
    }
    return true;
}
