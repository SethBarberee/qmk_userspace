/* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
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
#include "sethbarberee.h"
#include "version.h"

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
#if defined(BOOTLOADER_CATERINA)
    // Make sure the red LEDs don't light
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
    keyboard_pre_init_keymap();
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!is_keyboard_master()) {
        return state;
    }

    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#if defined(RGBLIGHT_ENABLE)
    state = layer_state_set_rgb_light(state);
#endif
    return layer_state_set_keymap(state);
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
#if defined(RGBLIGHT_ENABLE)
    keyboard_post_init_rgb_light();
#endif
#if defined(RGB_MATRIX_ENABLE)
    keyboard_post_init_rgb_matrix();
#endif

    keyboard_post_init_keymap();
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
#ifdef OLED_ENABLE
    oled_off();
#endif
    suspend_power_down_keymap();
}

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
    suspend_wakeup_init_keymap();
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_record_keymap(keycode, record)) {
        switch (keycode) {
            case KC_VRSN: // Prints firmware version
                if (record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
                }
                break;
            case KC_QWER: // Set default layer to QWERTY
                if (record->event.pressed) {
                    set_single_persistent_default_layer(_QWERTY);
                }
                break;
            case KC_COLE: // Set default layer to COLEMAK
                if (record->event.pressed) {
                    set_single_persistent_default_layer(_COLEMAK);
                }
                break;
            case KC_DVOR: // Set default layer to DVORAK
                if (record->event.pressed) {
                    set_single_persistent_default_layer(_DVORAK);
                }
                break;
            // RGB EEPROM stuff below is adapted from @drashna
            case KC_RGB_T:
                if (record->event.pressed) {
                    user_config.rgb_layer_change ^= 1;
                    dprintf("rgblight layer change [EEPROM]: %u\n", user_config.rgb_layer_change);
                    eeconfig_update_user(user_config.raw);
                    if (user_config.rgb_layer_change) {

#ifdef  RGB_MATRIX_ENABLE
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR);
#endif
#ifdef RGBLIGHT_ENABLE
                        rgblight_enable_noeeprom();
#endif
                        layer_state_set(layer_state); // This is needed to immediately set the layer color (looks better)
                    } else {
#ifdef  RGB_MATRIX_ENABLE
                        rgb_matrix_set_flags(LED_FLAG_ALL);
#endif
#ifdef RGBLIGHT_ENABLE
                        rgblight_disable_noeeprom();
#endif
                    }
                }
                break;
            case RGB_TOG:
                // Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
                if (record->event.pressed) {
#    else
                if (!record->event.pressed) {
#    endif
#ifdef RGBLIGHT_ENABLE
                    rgblight_toggle();
#endif
                    //rgb_matrix_toggle();
                }
                return false;
                break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // quantum_keycodes.h L400 for definitions
            if (record->event.pressed) {
                bool is_eeprom_updated = false;
                // This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
                if (user_config.rgb_layer_change) {
                    user_config.rgb_layer_change = false;
                    dprintf("rgblight layer change [EEPROM]: %u\n", user_config.rgb_layer_change);
                    is_eeprom_updated = true;
                }
                if (is_eeprom_updated) {
                    eeconfig_update_user(user_config.raw);
                }
            }
            break;
        }
    }
    return true;
}

/* Set defaults for EEPROM user configuration variables */
__attribute__((weak)) void eeconfig_init_keymap(void) {}
void eeconfig_init_user(void) {
    user_config.raw                           = 0;
    user_config.rgb_layer_change              = true;

    eeconfig_update_user(user_config.raw);
    eeconfig_init_keymap();
}

