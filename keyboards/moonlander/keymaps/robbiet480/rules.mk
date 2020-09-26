# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
COMMAND_ENABLE = no
WEBUSB_ENABLE = yes
ORYX_ENABLE = yes
WPM_ENABLE = yes
SRC = matrix.c
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_HID_ENABLE            = yes
ifeq ($(strip $(RGB_HID_ENABLE)), yes)
	RAW_ENABLE = yes

	# QMK doesn't have enough endpoints so we need to disable some features to get CONSOLE_ENABLE
	# MOUSEKEY_ENABLE = no   # Mouse keys
	# EXTRAKEY_ENABLE = no   # Audio control and System control
	# NKRO_ENABLE = no	    # USB Nkey Rollover

	# or

	CONSOLE_ENABLE = no
    SRC += rgb_hid_protocol.c
endif
