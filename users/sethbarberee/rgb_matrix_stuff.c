#include <stdint.h>
#include "sethbarberee.h"
#include "rgb_matrix.h"

void keyboard_post_init_rgb_matrix(void) {

}

__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max){
    return true;
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    if(!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) return false;


    if (user_config.rgb_layer_change)
    {
        for (uint8_t i = led_min; i < led_max; i++) {

            if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                switch(get_highest_layer(layer_state))
                {
                    case _LOWER:
                        rgb_matrix_set_color(i, RGB_GREEN);
                        break;
                    case _RAISE:
                        rgb_matrix_set_color(i, RGB_BLUE);
                        break;
                    case _ADJUST:
                        rgb_matrix_set_color(i, HSV_GOLDENROD);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return false;
}

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) {
    return true;
}

bool rgb_matrix_indicators_user(void) {
    return rgb_matrix_indicators_keymap();
}
