/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "muse.h"

enum preonic_layers {
  _BEPO,
  _RAISE
};

enum preonic_keycodes {
  BEPO = SAFE_RANGE,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Ç    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Z   |   B  |   É  |   P  |   O  |   È  |   ^  |   V  |   D  |   L  |   J  |  W   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   U  |   I  |   E  |   ;  |   C  |   T  |   S  |   R  |   N  |  M   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Ê    |   À  |   Y  |   X  |   .  |   K  |   '  |   Q  |   G  |   H  |   F  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Super| Del  | Shift| Alt  |Ctrl  |    Space    |Raise | AltGr| Shift| Bkspc|      |
 * `-----------------------------------------------------------------------------------'
 */
[_BEPO] = LAYOUT_preonic_grid( \
  KC_ESC,  BP_1, BP_2, BP_3, BP_4, BP_5, BP_6, BP_7, BP_8, BP_9, BP_0, BP_CCED, \
  BP_Z, BP_B, BP_ECUT, BP_P, BP_O, BP_EGRV, BP_DCRC, BP_V, BP_D, BP_L, BP_J, BP_W,  \
  KC_TAB, BP_A, BP_U, BP_I, BP_E, BP_COMM, BP_C, BP_T, BP_S, BP_R, BP_N, BP_M, \
  BP_ECRC, BP_AGRV, BP_Y, BP_X, BP_DOT, BP_K, BP_APOS, BP_Q, BP_G, BP_H, BP_F, KC_NO, \
  KC_LGUI, KC_DEL, KC_LSFT, KC_LALT, KC_LCTL,   KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_RSFT, KC_BSPC,   KC_NO \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   F1 |   F2 |  F3  |   F4 |  F5  |  F6  |   F7 |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   "  |   <  |   >  |   «  |   »  |   @  |   +  |   -  |   /  |   =  | PgUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  $   |  (   |  )   |  %   |  =   |  Play| Left |  Down|   Up | Right|  PgDn|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  #   |  [   |  ]   |  `   |  °   |  Mute| Volup|Voldn | Prev | Next | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Reset| Del  | Shift| Alt  |Ctrl  |    Enter    |Raise | AltGr| Shift| Bkspc| End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
  _______, BP_DQOT, BP_LESS, BP_GRTR, BP_LGIL, BP_RGIL, BP_AT, BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR,    KC_PGUP,  \
  _______,  BP_DLR,   BP_LPRN,   BP_RPRN,   BP_PERC,   BP_EQL,   KC_MPLY,   KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, KC_PGDN, \
  _______, BP_HASH,   BP_LBRC,   BP_RBRC,   BP_GRV,  BP_DEGR,  KC_MUTE,  KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, KC_HOME, \
  RESET, KC_DEL, KC_LSFT, KC_LALT, KC_LCTL, KC_ENTER, KC_ENTER, _______, KC_RALT, KC_RSFT, KC_BSPC, KC_END \
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case BEPO:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_BEPO);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
          } else {
            layer_off(_RAISE);
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
      return false;
    default:
      return true;
  }
}
