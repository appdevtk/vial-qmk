#include QMK_KEYBOARD_H
#include "keymap_german.h"

#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h"
#include "os_detection.h"

// The first four layers gets a name for readability
enum layers {
  _DEFAULT_MAC,
  _DEFAULT_WIN,
  _CODENGLISH,
  _LOWER_MAC,
  _LOWER_WIN,
  _RAISE_MAC,
  _RAISE_WIN,
  _ADJUST_1,
  _ADJUST_2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_DEFAULT_MAC] = LAYOUT(
	KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,  KC_0,     KC_GRV,
	KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                    KC_Y,  KC_U,    KC_I,    KC_O,  KC_P,     KC_MINS,
	KC_LCTL, KC_A, KC_S, KC_D,    KC_F,    KC_G,                    KC_H,  KC_J,    KC_K,    KC_L,  KC_SCLN,  KC_QUOT,
	KC_LSFT, KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	                     KC_LALT, KC_LGUI, MO(3), KC_SPC,  KC_ENT,  MO(5), KC_BSPC, KC_RGUI
      ),
      [_DEFAULT_WIN] = LAYOUT(
	KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,  KC_0,     KC_GRV,
	KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                    KC_Y,  KC_U,    KC_I,    KC_O,  KC_P,     KC_MINS,
	KC_LCTL, KC_A, KC_S, KC_D,    KC_F,    KC_G,                    KC_H,  KC_J,    KC_K,    KC_L,  KC_SCLN,  KC_QUOT,
	KC_LSFT, KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	                     KC_LALT, KC_LGUI, MO(3), KC_SPC,  KC_ENT,  MO(5), KC_BSPC, KC_RGUI
      ),
      [_CODENGLISH] = LAYOUT(
	KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,  KC_0,     KC_GRV,
	KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                    KC_Y,  KC_U,    KC_I,    KC_O,  KC_P,     KC_MINS,
	KC_LCTL, KC_A, KC_S, KC_D,    KC_F,    KC_G,                    KC_H,  KC_J,    KC_K,    KC_L,  KC_SCLN,  KC_QUOT,
	KC_LSFT, KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	                     KC_LALT, KC_LGUI, MO(3), KC_SPC,  KC_ENT,  MO(5), KC_BSPC, KC_RGUI
      ),
      [_LOWER_MAC] = LAYOUT(
	_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
	KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
	_______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
	                           _______, _______, _______, _______, _______, MO(7), _______, _______
      ),
      [_LOWER_WIN] = LAYOUT(
	_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
	KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
	_______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
	                           _______, _______, _______, _______, _______, MO(7), _______, _______
      ),
      [_RAISE_MAC] = LAYOUT(
	_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
	KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
	                           _______, _______, MO(7),   _______, _______, _______, _______, _______
      ),
      [_RAISE_WIN] = LAYOUT(
	_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
	KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
	                           _______, _______, MO(7),   _______, _______, _______, _______, _______
      ),
      [_ADJUST_1] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
	                           _______, _______, _______, _______, _______, _______, _______, _______
      ),
      [_ADJUST_2] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
	                           _______, _______, _______, _______, _______, _______, _______, _______
      )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [4] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [5] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [6] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [7] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [8] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

//#if defined(RGB_MATRIX_ENABLE)
void keyboard_post_init_keymap(void) {
    // extern led_config_t g_led_config;
}

void keyboard_post_init_user(void) {
    // Set default layer based on the detected OS after a 500 ms delay.
  uint32_t get_host_os(uint32_t trigger_time, void* cb_arg) {
    switch (detected_host_os()) {
      case OS_UNSURE:  // Don't change default layer if unsure.
        break;
      case OS_MACOS:   // On Mac, set default layer to _DEFAULT_MAC.
      case OS_IOS:
        set_single_persistent_default_layer(_DEFAULT_MAC);
        break;
      case OS_WINDOWS:   // On Windows, set default layer to _DEFAULT_WIN.
      case OS_LINUX:
        set_single_persistent_default_layer(_DEFAULT_WIN);
        break;
      default:         // Else, set to _DEFAULT_MAC.
        set_single_persistent_default_layer(_DEFAULT_MAC);
        break;
    }
    return 0;
  }
  defer_exec(1000, get_host_os, NULL);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = state | default_layer_state;
  state = update_tri_layer_state(state, _LOWER_MAC, _RAISE_MAC, _ADJUST_1);
  state = update_tri_layer_state(state, _DEFAULT_WIN, _LOWER_MAC, _LOWER_WIN);
  state = update_tri_layer_state(state, _DEFAULT_WIN, _RAISE_MAC, _RAISE_WIN);
  return state & ~default_layer_state;
}

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
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

void set_color_for_indicator(uint8_t index, uint8_t offset) {
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
//#endif
