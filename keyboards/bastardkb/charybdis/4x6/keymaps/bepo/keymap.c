/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
 #include "quantum/keymap_extras/keymap_bepo.h"

 #ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
 #    include "timer.h"
 #endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

 enum charybdis_keymap_layers {
     LAYER_BASE = 0,
     LAYER_LOWER,
     LAYER_RAISE,
     LAYER_POINTER,
 };

#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

 /** \brief Automatically enable sniping-mode on the pointer layer. */
 #define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

 #ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
 static uint16_t auto_pointer_layer_timer = 0;

 #    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
 #        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
 #    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

 #    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
 #        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
 #    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
 #endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

 #define LOWER MO(LAYER_LOWER)
 #define RAISE MO(LAYER_RAISE)
 #define PT_ECIR LT(LAYER_POINTER, BP_ECIR)
 #define PT_F LT(LAYER_POINTER, BP_F)

 #ifndef POINTING_DEVICE_ENABLE
 #    define DRGSCRL KC_NO
 #    define DPI_MOD KC_NO
 #    define S_D_MOD KC_NO
 #    define SNIPING KC_NO
 #endif // !POINTING_DEVICE_ENABLE


 // clang-format off
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [LAYER_BASE] = LAYOUT(
   // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_ESC, BP_DLR,  BP_DQUO, BP_LDAQ, BP_RDAQ,  BP_LPRN,   BP_RPRN,   BP_AT, BP_PLUS,  BP_MINS, BP_SLSH, BP_ASTR,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_TAB,     BP_B, BP_EACU,    BP_P,    BP_O, BP_EGRV,    BP_DCIR,    BP_V,    BP_D,    BP_L,    BP_J,    BP_Z,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LGUI,     BP_A,    BP_U,    BP_I,    BP_E, BP_COMM,       BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    BP_M,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LCTL,  PT_ECIR, BP_AGRV,    BP_Y,    BP_X,  BP_DOT,       BP_K, BP_QUOT,    BP_Q,    BP_G,    BP_H,    PT_F,
   // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    KC_BSPC,   KC_SPC, LOWER,      RAISE,  KC_ENT,
                                           KC_LSFT,  KC_RALT,         KC_DEL
   //                            ╰───────────────────────────╯ ╰──────────────────╯
   ),

   [LAYER_LOWER] = LAYOUT(
   // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_TILD,    BP_1,    BP_2,    BP_3,    BP_4,    BP_5,       BP_6,    BP_7,    BP_8,    BP_9,    BP_0, BP_DEG,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         RGB_MOD, XXXXXXX, XXXXXXX, LCTL(BP_Z), LCTL(BP_Y), XXXXXXX,    BP_LBRC,   KC_P7,   KC_P8,   KC_P9, BP_RBRC, XXXXXXX,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         RGB_TOG, BP_CCED,    BP_W, LCTL(BP_C), LCTL(BP_V), XXXXXXX,    BP_PLUS,   KC_P4,   KC_P5,   KC_P6, BP_MINS,  BP_EQL,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        RGB_RMOD, XXXXXXX, XXXXXXX, LCTL(BP_A), LCTL(BP_X), XXXXXXX,    BP_ASTR,   KC_P1,   KC_P2,   KC_P3, BP_SLSH, BP_DOT,
   // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______,
                                            KC_LSFT, KC_RALT,      KC_P0
   //                            ╰───────────────────────────╯ ╰──────────────────╯
   ),

   [LAYER_RAISE] = LAYOUT(
   // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_MNXT, XXXXXXX, XXXXXXX,  KC_UP, XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_MPLY, XXXXXXX,KC_LEFT , KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_MUTE,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
   // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    _______, _______, XXXXXXX,    _______, XXXXXXX,
                                            _______, _______,    XXXXXXX
   //                            ╰───────────────────────────╯ ╰──────────────────╯
   ),

   [LAYER_POINTER] = LAYOUT(
   // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
   // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
   // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                            XXXXXXX, KC_BTN2,    KC_BTN2
   //                            ╰───────────────────────────╯ ╰──────────────────╯
   )
 };
 // clang-format on

 #ifdef POINTING_DEVICE_ENABLE
 #    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
 report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
     if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
         if (auto_pointer_layer_timer == 0) {
             layer_on(LAYER_POINTER);
 #        ifdef RGB_MATRIX_ENABLE
             rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
             rgb_matrix_sethsv_noeeprom(HSV_GREEN);
 #        endif // RGB_MATRIX_ENABLE
         }
         auto_pointer_layer_timer = timer_read();
     }
     return mouse_report;
 }

 void matrix_scan_user(void) {
     if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
         auto_pointer_layer_timer = 0;
         layer_off(LAYER_POINTER);
 #        ifdef RGB_MATRIX_ENABLE
         rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
 #        endif // RGB_MATRIX_ENABLE
     }
 }
 #    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

 #    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
 layer_state_t layer_state_set_user(layer_state_t state) {
     charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
     return state;
 }
 #    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
 #endif     // POINTING_DEVICE_ENABLE

 #ifdef RGB_MATRIX_ENABLE
 // Forward-declare this helper function since it is defined in rgb_matrix.c.
 void rgb_matrix_update_pwm_buffers(void);
 #endif

