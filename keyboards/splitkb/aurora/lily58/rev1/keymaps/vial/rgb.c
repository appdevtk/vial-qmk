// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "lily58_vial.h"
#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h"

void keymap_rgb_post_init(void) {
    static const keypos_t modifier_keys[] = {
        {.row = 2, .col = 0},
        {.row = 3, .col = 0},
        {.row = 4, .col = 1},
        {.row = 4, .col = 2},
        {.row = 4, .col = 3},
        {.row = 4, .col = 4},
        {.row = 9, .col = 1},
        {.row = 8, .col = 0},
        {.row = 9, .col = 4},
        {.row = 9, .col = 3},
        {.row = 9, .col = 2},
    };

    for (uint8_t i = 0; i < sizeof(modifier_keys) / sizeof(modifier_keys[0]); ++i) {
        uint8_t led = g_led_config.matrix_co[modifier_keys[i].row][modifier_keys[i].col];
        if (led != NO_LED) {
            g_led_config.flags[led] = LED_FLAG_MODIFIER;
        }
    }
}

static void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        case 1: // breathing
        {
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb_nocie(hsv);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default: // Solid Color
        {
            RGB rgb = hsv_to_rgb_nocie(hsv);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}

static void set_color_for_indicator(uint8_t index, uint8_t offset) {
    uint8_t max_indicators = 6;
    //HSV hsv = {HSV_PURPLE};
    HSV hsv = rgb_matrix_config.hsv;
    //Clamp brightness
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    //Rotate hue
    hsv.h = (hsv.h + 255 / (max_indicators + 1) * offset) % 255;
    RGB rgb = hsv_to_rgb_nocie(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case _RAISE_MAC:
        case _RAISE_WIN:
            rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
            break;
        case _LOWER_MAC:
        case _LOWER_WIN:
            rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
            break;
        case _ADJUST_1:
        case _ADJUST_2:
            rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
            break;
        case _CODENGLISH:
            rgb_matrix_layer_helper(HSV_BLUE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
            break;
        default: {
            rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW, led_min, led_max);
            break;
        }
    }
    rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);

    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (keycode == KC_NO) {
                        rgb_matrix_set_color(index, RGB_OFF);
                    } else if (keycode >= KC_F1 && keycode <= KC_F12) {
                        set_color_for_indicator(index, 1);
                    } else if (keycode >= KC_PRINT_SCREEN && keycode <= KC_PAGE_DOWN) {
                        set_color_for_indicator(index, 2);
                    } else if (keycode >= KC_RIGHT && keycode <= KC_UP) {
                        set_color_for_indicator(index, 3);
                    } else if (keycode >= KC_KP_SLASH && keycode <= KC_KP_ENTER) {
                        set_color_for_indicator(index, 4);
                    } else if (keycode >= KC_KP_1 && keycode <= KC_KP_0) {
                        set_color_for_indicator(index, 5);
                    } else if (keycode >= KC_KP_DOT && keycode <= KC_KP_EQUAL) {
                        set_color_for_indicator(index, 4);
                    } else if (keycode > KC_0) {
                        set_color_for_indicator(index, 6);
                    }
                }
            }
        }
    }
    return false;
}
