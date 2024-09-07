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
#pragma once
#include "sethbarberee.h"

//Define a type for as many tap dance states as you need
typedef enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
} td_state_t;


enum {
    TD_ECAP = 0,
    TAP_DANCE_MAX
};

#define KC_ECAP TD(TD_ECAP)

typedef struct {
    bool toggled; // store whether we have toggled caps lock
#ifdef RGBLIGHT_ENABLE
    int normal_mode;
#endif // RGBLIGHT_ENABLE
    td_state_t state;
} td_tap_t;

extern tap_dance_action_t tap_dance_actions[TAP_DANCE_MAX];
