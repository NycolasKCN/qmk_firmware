/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

//#define USE_MATRIX_I2

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define HOLD_ON_OTHER_KEY_PRESS

#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_SLEEP // turn off effects when suspended

#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SOLID_SPLASH


#ifdef RGBLIGHT_ENABLE
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10
#endif

#define MOUSEKEY_DELAY              10
#define MOUSEKEY_INTERVAL           15
#define MOUSEKEY_MOVE_DELTA	        5
#define MOUSEKEY_MAX_SPEED	        3
#define MOUSEKEY_TIME_TO_MAX	    25

#define MOUSEKEY_WHEEL_DELAY	    10
#define MOUSEKEY_WHEEL_INTERVAL	    80
#define MOUSEKEY_WHEEL_DELTA	    1
#define MOUSEKEY_WHEEL_MAX_SPEED	8
#define MOUSEKEY_WHEEL_TIME_TO_MAX	40
