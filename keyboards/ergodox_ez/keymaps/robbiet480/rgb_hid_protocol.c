#include QMK_KEYBOARD_H
#include "raw_hid.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

enum hid_commands
{
  hid_version = 0x01,
  hid_rgblight_enable,
  hid_rgblight_disable,
  hid_rgblight_toggle,
  hid_rgblight_set_mode,
  hid_rgblight_get_mode,
  hid_rgblight_sethsv,
  hid_rgblight_setrgb,
  hid_rgblight_increase_val,
  hid_rgblight_decrease_val,
  hid_rgblight_increase_sat,
  hid_rgblight_decrease_sat,
  hid_rgblight_increase_hue,
  hid_rgblight_decrease_hue
};

void raw_hid_receive( uint8_t *data, uint8_t length ) {
  #ifdef CONSOLE_ENABLE
  uprintf("Received hid command 0x0%u\n", data[0]);
  #endif
  switch (data[0])
  {
    case hid_version:
      data[0] = 0x0;
	    data[1] = 0x2;
	    break;
    case hid_rgblight_enable:
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_enable();
        #else
        rgblight_enable();
        #endif
	    break;
    case hid_rgblight_disable:
	    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_disable();
        #else
        rgblight_disable();
        #endif
	    break;
    case hid_rgblight_toggle:
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_toggle();
        #else
        rgblight_toggle();
        #endif
	    break;
	  case hid_rgblight_set_mode:
	    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode(data[1]);
        #else
        rgblight_mode(data[1]);
        #endif
	    break;
	  case hid_rgblight_get_mode:
        #ifdef RGB_MATRIX_ENABLE
        data[1] = rgb_matrix_get_mode();
        #else
        data[1] = rgblight_get_mode();
        #endif
	    break;
	  case hid_rgblight_sethsv:
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
    case hid_rgblight_setrgb:
      {
          // 1,2,3 = r,g,b
          // 4,5,6 side,start,end
          print("Received set RGB request\n");
          #ifdef RGB_MATRIX_ENABLE
          if(sizeof(data) == 5) {
              #ifdef CONSOLE_ENABLE
              uprintf("Setting single key RGB color via rgb_matrix: %u %u %u %u\n", data[1], data[2], data[3], data[4]);
              #endif
              rgb_matrix_set_color(data[1], data[2], data[3], data[4]);
          } else {
              #ifdef CONSOLE_ENABLE
              uprintf("Setting all RGB colors via rgb_matrix: %u %u %u\n", data[1], data[2], data[3]);
              #endif
              rgb_matrix_set_color_all(data[1], data[2], data[3]);
          }
          #else
          if(sizeof(data) == 5) {
              #ifdef CONSOLE_ENABLE
              uprintf("Setting single key RGB color via rgblight: %u %u %u %u\n", data[1], data[2], data[3], data[4]);
              #endif
              rgblight_setrgb_at(data[1], data[2], data[3], data[4]);
          } else if(sizeof(data) == 6) {
              #ifdef CONSOLE_ENABLE
              uprintf("Setting range of key RGB colors via rgblight: %u %u %u %u %u\n", data[1], data[2], data[3], data[4], data[5]);
              #endif
              rgblight_setrgb_range(data[1], data[2], data[3], data[4], data[5]);
          } else {
              if (data[4] == 1) {
                  #ifdef CONSOLE_ENABLE
                  uprintf("Setting master RGB colors via rgblight: %u %u %u\n", data[1], data[2], data[3]);
                  #endif
                  rgblight_setrgb_master(data[1], data[2], data[3]);
              } else if (data[4] == 2) {
                  #ifdef CONSOLE_ENABLE
                  uprintf("Setting slave RGB colors via rgblight: %u %u %u\n", data[1], data[2], data[3]);
                  #endif
                  rgblight_setrgb_slave(data[1], data[2], data[3]);
              } else {
                  #ifdef CONSOLE_ENABLE
                  uprintf("Setting all RGB colors via rgblight: %u %u %u\n", data[1], data[2], data[3]);
                  #endif
                  rgblight_setrgb(data[1], data[2], data[3]);
              }
          }
          #endif
        break;
      }
    case hid_rgblight_increase_val:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_increase_val();
      #else
      rgblight_increase_val();
      #endif
      break;
    case hid_rgblight_decrease_val:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_decrease_val();
      #else
      rgblight_decrease_val();
      #endif
      break;
    case hid_rgblight_increase_sat:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_increase_sat();
      #else
      rgblight_increase_sat();
      #endif
      break;
    case hid_rgblight_decrease_sat:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_decrease_sat();
      #else
      rgblight_decrease_sat();
      #endif
      break;
    case hid_rgblight_increase_hue:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_increase_hue();
      #else
      rgblight_increase_hue();
      #endif
      break;
    case hid_rgblight_decrease_hue:
      #ifdef RGB_MATRIX_ENABLE
      rgb_matrix_decrease_hue();
      #else
      rgblight_decrease_hue();
      #endif
      break;
	  default:
	    data[0] = 0xFF;
	    break;
  }

  raw_hid_send(data, length);
}
