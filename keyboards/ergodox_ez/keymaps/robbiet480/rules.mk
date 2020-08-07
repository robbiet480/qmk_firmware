# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LINK_TIME_OPTIMIZATION_ENABLE = yes
COMMAND_ENABLE = no
WEBUSB_ENABLE = no
ORYX_ENABLE = no
SRC = matrix.c
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
WPM_ENABLE = yes
RGB_HID_ENABLE            = yes
ifeq ($(strip $(RGB_HID_ENABLE)), yes)
	RAW_ENABLE = yes
    SRC += rgb_hid_protocol.c
endif
