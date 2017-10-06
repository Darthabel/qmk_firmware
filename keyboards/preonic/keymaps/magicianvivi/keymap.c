#include "preonic.h"
#include "action_layer.h"
#include "keymap_bepo.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BEPO 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum preonic_keycodes {
  BEPO = SAFE_RANGE,
  LOWER,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Bepo
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Ç    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Z    |   B  |   É  |   P  |   O  |  Del | Bksp |   V  |   D  |   L  |   J  | W    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   U  |   I  |   E  | ,    |   C  |   T  |   S  |   R  |  N   | M    |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   À  |   Y  |   X  |   .  |   K  | Shift| Shift|   Q  |   G  |   H  |   F  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps | AltGr| Super| Alt  | CTRL |      Space  |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BEPO] = {
  {KC_ESC, BP_1, BP_2, BP_3, BP_4, BP_5, BP_6, BP_7, BP_8, BP_9, BP_0, BP_CCED},
  {BP_Z, BP_B, BP_ECUT, BP_P, BP_O, KC_DEL, KC_BSPC, BP_V, BP_D, BP_L, BP_J, BP_W},
  {KC_TAB, BP_A, BP_U, BP_I, BP_E, BP_COMM, BP_C, BP_T, BP_S, BP_R, BP_N, BP_M},
  {BP_AGRV, BP_Y, BP_X, BP_DOT, BP_K, KC_LSFT, KC_RSFT, BP_Q, BP_G, BP_H, BP_F, KC_ENTER},
  {KC_CAPS, BP_ALGR, KC_LGUI, KC_LALT, KC_LCTL, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |      |      |      |      |      |      |   /  |   *  |   -  |   %  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   F1 |   F2 |   F3 |   F4 |      |      |   7  |   8  |   9  |   +  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |  F5  |  F6  |  F7  |  F8  |      |      |   4  |   5  |   6  |   =  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |  F9  |  F10 |  F11 |  F12 |      |      |   1  |   2  |   3  |Enter | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps | AltGr| Super| Alt  |      |      0      |ADJUST| Home | Down | Up   | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BP_SLSH, BP_ASTR, BP_MINS, BP_PERC, XXXXXXX},
  {XXXXXXX, KC_F1, KC_F2,   KC_F3, KC_F4, XXXXXXX, XXXXXXX, BP_7, BP_8, BP_9, BP_PLUS, XXXXXXX},
  {KC_LCTL,  KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,  XXXXXXX, BP_4, BP_5, BP_6, BP_EQL, XXXXXXX},
  {KC_LSFT, KC_F9,   KC_F10,   KC_F11,   KC_F12, XXXXXXX, XXXXXXX, BP_1, BP_2, BP_3, KC_ENTER, KC_RSFT},
  {KC_CAPS, BP_ALGR, KC_LGUI, KC_LALT, _______, BP_0, BP_0, RAISE, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   F1 |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   «  |   "  |   |  |  %   |   =  |   !  |   ^  |   +  |   -  |   /  |   *  |   »  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Ù   |   $  |  <   |  {   |  (   |  [   |   ]  |   )  |   }  |   >  |   @  |    ` |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  Ê   |   #  |   °  |   &  |  \   | Shift| Shift|   '  |   ?  |   ~  |   …  |    È |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | AltGr| Super| Alt  |ADJUST|      _      |      | Home | Down |  Up  | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12},
  {BP_LGIL, BP_DQOT, BP_PIPE, BP_PERC, BP_EQL, S(BP_DCRC), BP_DCRC, BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, BP_RGIL},
  {BP_UGRV, BP_DLR, BP_LESS, BP_LCBR, BP_LPRN, BP_LBRC, BP_RBRC, BP_RPRN, BP_RCBR, BP_GRTR, BP_AT, BP_GRV},
  {BP_ECRC, BP_HASH, BP_DEGR, BP_AMPR, BP_BSLS, KC_LSFT, KC_RSFT, BP_APOS, BP_QEST, BP_TILD, BP_ELPS, BP_EGRV},
  {XXXXXXX, BP_ALGR, KC_LGUI, KC_LALT, LOWER, BP_UNDS, BP_UNDS, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|      |      |Bepo  |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  XXXXXXX, XXXXXXX, BEPO,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX},
  {XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
}


};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_bepo[][2]     = SONG(QWERTY_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case BEPO:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_bepo, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_BEPO);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
