#include QMK_KEYBOARD_H
#include "version.h"
#include "raw_hid.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  HSV_172_255_255,
  HSV_86_255_128,
  HSV_27_255_255,
  ST_MACRO_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 LCTL(LSFT(KC_MEDIA_EJECT)),KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
    LT(1,KC_GRAVE), KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           ST_MACRO_0,                                     LALT(LCTL(LSFT(KC_M))),KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,
    LT(2,KC_NO),    KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      LGUI(KC_BSLASH),
    KC_LSPO,        LCTL_T(KC_Z),   KC_X,           KC_C,           KC_V,           KC_B,           KC_HYPR,                                        KC_MEH,         KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RSPC,
    KC_GRAVE,       KC_QUOTE,       KC_LGUI,        KC_LEFT,        KC_RIGHT,                                                                                                       KC_UP,          KC_DOWN,        KC_LBRACKET,    KC_RBRACKET,    MO(1),
                                                                                                    KC_PGDOWN,      KC_PGUP,        KC_TRANSPARENT, RCTL_T(KC_ESCAPE),
                                                                                                                    KC_LALT,        KC_RALT,
                                                                                    KC_SPACE,       KC_TAB,         KC_LGUI,        KC_RGUI,        KC_BSPACE,      KC_ENTER
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_F12,
    KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,                                                                       KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_LBRACKET,    KC_RBRACKET,    KC_TILD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_AMPR,        KC_1,           KC_2,           KC_3,           KC_BSLASH,      KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EQUAL,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_DOT,         KC_0,           KC_EQUAL,       KC_TRANSPARENT,
                                                                                                    RGB_MOD,        HSV_172_255_255,RGB_TOG,        RGB_SLD,
                                                                                                                    HSV_86_255_128, KC_TRANSPARENT,
                                                                                    RGB_VAD,        RGB_VAI,        HSV_27_255_255, KC_TRANSPARENT, RGB_HUD,        RGB_HUI
  ),
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, DEBUG,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,                                                                                                     KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {0,0,0}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {0,0,0}, {0,0,0}, {0,0,0}, {134,255,213} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {15,166,195}, {0,205,155}, {0,205,155}, {0,0,0}, {0,183,238}, {0,183,238}, {31,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,183,238}, {0,0,0}, {0,0,0}, {0,0,0}, {0,183,238}, {0,183,238}, {0,183,238}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,183,238}, {0,183,238}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
        SEND_STRING(SS_LALT(SS_LCTL(SS_LSFT(SS_TAP(X_M)))));
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_172_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(172,255,255);
      }
      return false;
    case HSV_86_255_128:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(86,255,128);
      }
      return false;
    case HSV_27_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(27,255,255);
      }
      return false;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

  uint8_t layer = biton32(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }

  uint8_t hid_data[32] = {0x05, layer};
  #ifdef CONSOLE_ENABLE
  uprintf("Sending for layer change with %u enabled layers: 0x%u\n", sizeof(keymaps)/sizeof(keymaps[0]), hid_data);
  #endif

  raw_hid_send(hid_data, 32);

  return state;
};

enum hid_commands
{
  hid_version                 = 0x01,
  hid_get_state               = 0x02,
  hid_reset_qmk               = 0x03,
  hid_get_layer_count         = 0x04,
  hid_get_layer               = 0x05,
  hid_set_layer               = 0x06,
  hid_get_wpm                 = 0x07,
  hid_lighting_enable         = 0x08,
  hid_lighting_disable        = 0x09,
  hid_lighting_toggle         = 0x10,
  hid_lighting_set_mode       = 0x11,
  hid_lighting_get_mode       = 0x12,
  hid_lighting_sethsv         = 0x13,
  hid_lighting_increase_hue   = 0x14,
  hid_lighting_decrease_hue   = 0x15,
  hid_lighting_increase_sat   = 0x16,
  hid_lighting_decrease_sat   = 0x17,
  hid_lighting_increase_val   = 0x18,
  hid_lighting_decrease_val   = 0x19,
  hid_led_on                  = 0x20,
  hid_led_off                 = 0x21,
  hid_led_brightness          = 0x22
};

void raw_hid_receive( uint8_t *data, uint8_t length ) {
  #ifdef CONSOLE_ENABLE
  uprintf("Received hid command length %u: 0x0%u\n", length, data[0]);
  #endif

  switch (data[0])
  {
    case hid_version:
      data[0] = 0x0;
	    data[1] = 0x2;
	    break;
    case hid_get_state:
        // State spec
        // Position 0: Always 0x02
        // Position 1: Lighting type (0 for none, 1 for RGB matrix, 2 for RGB light)
        // Position 2: Enabled status
        // Position 3: Hue first bit. Hue is 0 - 360, uint8_t is 0 - 255, so we split into two entries.
        // Position 4: Hue second bit
        // Position 5: Sat
        // Position 6: Val
        // Position 7: Mode
        // Position 8: Speed
        // Position 9: Enabled effects (not yet implemented but will be a mask)
        // Position 10: # of layers
        // Position 11: Active layer
        // Position 12: Whether WPM is enabled
        // Position 13: Status LED position (none is 0, left is 1, right is 2, both sides is 3)
        // gets packed values of: rgb lighting type, hsv, animation mode & speed, layers count, active layer, wpm enabled, status LED position
        #ifdef RGB_MATRIX_ENABLE
        data[1] = 0x01;
        data[2] = rgb_matrix_config.enable;
        uint8_t hue_0_255 = (rgb_matrix_config.hsv.h >> 8) & 0xFF;
        uint8_t hue_256_360 = rgb_matrix_config.hsv.h & 0xFF;
        data[3] = hue_0_255;
        data[4] = hue_256_360;
        data[5] = rgb_matrix_config.hsv.s;
        data[6] = rgb_matrix_config.hsv.v;
        data[7] = rgb_matrix_get_mode();
        data[8] = rgb_matrix_config.speed;
        data[9] = 0xFF;
        #elif defined(RGBLIGHT_ENABLE)
        data[1] = 0x02;
        data[2] = rgblight_is_enabled();
        uint8_t hue_0_255 = (rgblight_get_hue() >> 8) & 0xFF;
        uint8_t hue_256_360 = rgblight_get_hue() & 0xFF;
        data[3] = hue_0_255;
        data[4] = hue_256_360;
        data[5] = rgblight_get_sat();
        data[6] = rgblight_get_val();
        data[7] = rgblight_config.mode;
        data[8] = rgblight_get_speed();
        data[9] = 0xFF;
        #else
        data[1] = 0x00;
        data[2] = 0xFF;
        data[3] = 0xFF;
        data[4] = 0xFF;
        data[5] = 0xFF;
        data[6] = 0xFF;
        data[7] = 0xFF;
        data[8] = 0xFF;
        data[9] = 0xFF;
        #endif

        #ifdef CONSOLE_ENABLE
        uprintf("Color bits: System: %u, Enabled: %u, Hue: %u, Sat: %u, Val: %u, Mode: %u, Speed: %u, Enabled effects: %u\n", data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
        #endif

        data[10] = sizeof(keymaps)/sizeof(keymaps[0]);
        data[11] = biton32(layer_state);
        #ifdef WPM_ENABLE
        data[12] = 0x01;
        #else
        data[12] = 0x00;
        #endif
        #ifdef LEFT_LEDS
        data[13] = 0x01;
        #else
        data[13] = 0x02;
        #endif

        #ifdef CONSOLE_ENABLE
        uprintf("Sending state %u\n", data);
        #endif
        break;
    case hid_reset_qmk:
        #ifdef CONSOLE_ENABLE
        print("Reset!");
        #endif
        reset_keyboard();
        break;
    case hid_get_layer_count:
        #ifdef CONSOLE_ENABLE
        uprintf("Returning layer count of %u\n", sizeof(keymaps)/sizeof(keymaps[0]));
        #endif
        data[1] = sizeof(keymaps)/sizeof(keymaps[0]);
        break;
    case hid_get_layer:
        #ifdef CONSOLE_ENABLE
        uprintf("Returning active layer %u\n", biton32(layer_state));
        #endif
        data[1] = biton32(layer_state);
        break;
    case hid_set_layer:
        #ifdef CONSOLE_ENABLE
        uprintf("Setting active layer to %u\n", data[1]);
        #endif
        layer_move(data[1]);
        break;
    case hid_get_wpm:
        #ifdef WPM_ENABLE
        data[1] = get_current_wpm();
        #ifdef CONSOLE_ENABLE
        uprintf("Returning WPM: %u\n", data[1]);
        #endif
        #else
        data[1] = 0xFF;
        #endif
        break;
    case hid_lighting_enable:
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_enable();
        #else
        rgblight_enable();
        #endif
	    break;
    case hid_lighting_disable:
	    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_disable();
        #else
        rgblight_disable();
        #endif
	    break;
    case hid_lighting_toggle:
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_toggle();
        #else
        rgblight_toggle();
        #endif
	    break;
	  case hid_lighting_set_mode:
	    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode(data[1]);
        #else
        rgblight_mode(data[1]);
        #endif
	    break;
	  case hid_lighting_get_mode:
        #ifdef RGB_MATRIX_ENABLE
        data[1] = rgb_matrix_get_mode();
        #else
        data[1] = rgblight_get_mode();
        #endif
	    break;
	  case hid_lighting_sethsv:
      {
        // Hue is 0 - 360, uint8_t is 0 - 255
        // so we split into two entries.
        uint16_t hue = (data[1] << 8) + data[2];
        #ifdef RGB_MATRIX_ENABLE
            #ifdef CONSOLE_ENABLE
            uprintf("Setting all HSV colors via rgb_matrix: %u %u %u\n", hue, data[3], data[4]);
            #endif
            rgb_matrix_sethsv(hue, data[3], data[4]);
            // rgb_matrix_set_color_all(RGB_GOLDENROD);
        #else
            if(sizeof(data) == 6) {
                rgblight_sethsv_at(hue, data[3], data[4], data[5]);
            } else if(sizeof(data) == 7) {
                rgblight_sethsv_range(hue, data[3], data[4], data[5], data[6]);
            } else {
                rgblight_sethsv(hue, data[3], data[4]);
            }
        #endif
        break;
      }
    case hid_lighting_increase_hue:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_increase_hue();
      #else
      rgblight_increase_hue();
      #endif
      break;
    case hid_lighting_decrease_hue:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_decrease_hue();
      #else
      rgblight_decrease_hue();
      #endif
      break;
    case hid_lighting_increase_sat:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_increase_sat();
      #else
      rgblight_increase_sat();
      #endif
      break;
    case hid_lighting_decrease_sat:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_decrease_sat();
      #else
      rgblight_decrease_sat();
      #endif
      break;
    case hid_lighting_increase_val:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_increase_val();
      #else
      rgblight_increase_val();
      #endif
      break;
    case hid_lighting_decrease_val:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_decrease_val();
      #else
      rgblight_decrease_val();
      #endif
      break;
    case hid_led_on:
        if (data[2] == 6) {
            #ifdef CONSOLE_ENABLE
            print("Blink all LEDs");
            #endif
            ergodox_blink_all_leds();
        } else if (data[2] == 5) {
            #ifdef CONSOLE_ENABLE
            print("Turn ON board LED");
            #endif
            ergodox_board_led_on();
        } else if (data[2] == 4) {
            #ifdef CONSOLE_ENABLE
            print("Turn ON all LEDs");
            #endif
            ergodox_led_all_on();
        } else {
            if (data[1] == 0) {
                #ifdef LEFT_LEDS
                    #ifdef CONSOLE_ENABLE
                    uprintf("Turn ON left LED %u\n", data[2]);
                    #endif
                    if (data[2] == 1) {
                        ergodox_left_led_1_on();
                    } else if (data[2] == 2) {
                        ergodox_left_led_2_on();
                    } else if (data[2] == 3) {
                        ergodox_left_led_3_on();
                    }
                #endif
            } else if (data[1] == 0) {
                #ifdef CONSOLE_ENABLE
                uprintf("Turn ON right LED %u\n", data[2]);
                #endif
                ergodox_right_led_on(data[2]);
            }
        }
        break;
    case hid_led_off:
        if (data[2] == 5) {
            #ifdef CONSOLE_ENABLE
            print("Turn OFF board LED");
            #endif
            ergodox_board_led_off();
        } else if (data[2] == 4) {
            #ifdef CONSOLE_ENABLE
            print("Turn OFF all LEDs");
            #endif
            ergodox_led_all_off();
        } else {
            if (data[1] == 0) {
                #ifdef LEFT_LEDS
                    #ifdef CONSOLE_ENABLE
                    uprintf("Turn OFF left LED %u\n", data[2]);
                    #endif
                    if (data[2] == 1) {
                        ergodox_left_led_1_off();
                    } else if (data[2] == 2) {
                        ergodox_left_led_2_off();
                    } else if (data[2] == 3) {
                        ergodox_left_led_3_off();
                    }
                #endif
            } else if (data[1] == 0) {
                #ifdef CONSOLE_ENABLE
                uprintf("Turn OFF right LED %u\n", data[2]);
                #endif
                ergodox_right_led_off(data[2]);
            }
        }
        break;
    case hid_led_brightness:
        #ifdef CONSOLE_ENABLE
        uprintf("Set right LED #%u to brightness %u\n", data[1], data[2]);
        #endif
        ergodox_right_led_set(data[1], data[2]);
        break;
    default:
        data[0] = 0xFF;
    break;
  }

  raw_hid_send(data, length);
}
