#include QMK_KEYBOARD_H
#include "raw_hid.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

enum hid_commands
{
  hid_version   = 0x01,
  hid_get_state,
  hid_reset_qmk,
  hid_get_layer,
  hid_set_layer,
  hid_get_wpm,
  hid_lighting_enable,
  hid_lighting_disable,
  hid_lighting_toggle,
  hid_lighting_set_mode,
  hid_lighting_get_mode,
  hid_lighting_sethsv,
  hid_lighting_increase_hue,
  hid_lighting_decrease_hue,
  hid_lighting_increase_sat,
  hid_lighting_decrease_sat,
  hid_lighting_increase_val,
  hid_lighting_decrease_val,
  hid_led_on,
  hid_led_off,
  hid_led_brightness
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
        // Position 10: Previously it was # of layers
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

        data[10] = 0xFF;
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
