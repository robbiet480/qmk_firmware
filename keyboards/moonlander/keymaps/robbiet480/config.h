/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define FIRMWARE_VERSION u8"xbJpL/wy5xo"
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_RAINDROPS
#define RGB_MATRIX_STARTUP_SPD 60

#ifdef AUDIO_ENABLE
  #define CLOSE_ENCOUNTERS_5_NOTE_RT B__NOTE(_G8), B__NOTE(_A8), B__NOTE(_F8), B__NOTE(_F6), B__NOTE(_C8),
  #define STARTUP_SONG SONG(CLOSE_ENCOUNTERS_5_NOTE_RT)
#endif
