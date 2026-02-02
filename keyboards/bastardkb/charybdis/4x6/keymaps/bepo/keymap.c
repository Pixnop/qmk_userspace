/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * BÉPO layout optimized for programming - by Pixnop
 *
 * Optimisations:
 * - Symboles de programmation en accès direct sur LOWER
 * - Pas de doublons entre layers
 * - Pavé numérique main droite sur LOWER
 * - Navigation + F-keys + accents français sur RAISE
 * - Trackball sur le côté droit (5 thumbs gauche, 3 thumbs droit)
 */
#include QMK_KEYBOARD_H
#include "quantum/keymap_extras/keymap_bepo.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif
#endif

// Layer keys
#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_ECIR LT(LAYER_POINTER, BP_ECIR)
#define PT_F LT(LAYER_POINTER, BP_F)

// Pointing device fallbacks
#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
  // LAYER_BASE - BÉPO
  // ╰──────────────────────────────────────────────────────╯ ╰──────────────────────────────────────────────────────╯
  [LAYER_BASE] = LAYOUT(
        KC_ESC,  BP_DLR, BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN,    BP_RPRN,   BP_AT, BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR,
        KC_TAB,    BP_B,    BP_W,    BP_P,    BP_O, BP_EACU,    BP_DCIR,    BP_V,    BP_D,    BP_L,    BP_J,    BP_Z,
       KC_LGUI,    BP_A,    BP_U,    BP_I,    BP_E, BP_COMM,       BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    BP_M,
       KC_LCTL, PT_ECIR, BP_AGRV,    BP_Y,    BP_X,  BP_DOT,       BP_K, BP_QUOT,    BP_Q,    BP_G,    BP_H,    PT_F,
                                   KC_BSPC,  KC_SPC,   LOWER,      RAISE,  KC_ENT,
                                           KC_LSFT, KC_RALT,         KC_DEL
  ),

  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
  // LAYER_LOWER - Symboles programmation + Pavé numérique
  // ╰──────────────────────────────────────────────────────╯ ╰──────────────────────────────────────────────────────╯
  [LAYER_LOWER] = LAYOUT(
       BP_GRV, BP_HASH, BP_EXLM, BP_QUES, BP_SCLN, BP_COLN,     BP_EQL,  KC_NUM, BP_ASTR, BP_MINS, BP_PLUS, KC_BSPC,
        KC_TAB, BP_PIPE, BP_BSLS, BP_TILD, BP_UNDS, LCTL(BP_Z), BP_LBRC,   KC_P7,   KC_P8,   KC_P9, BP_RBRC,  KC_DEL,
        KC_ESC, BP_LABK, BP_RABK, BP_AMPR, LCTL(BP_Y), LCTL(BP_C), BP_LPRN, KC_P4, KC_P5,   KC_P6, BP_RPRN,  BP_EQL,
       BP_PERC, BP_LCBR, BP_RCBR, LCTL(BP_A), LCTL(BP_X), LCTL(BP_V), BP_EURO, KC_P1, KC_P2, KC_P3,  BP_DOT,  KC_ENT,
                                   _______, _______, _______,    QK_LLCK, KC_P0,
                                           KC_LSFT, KC_RALT,     BP_DOT
  ),

  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
  // LAYER_RAISE - Navigation + F-keys + Accents français
  // ╰──────────────────────────────────────────────────────╯ ╰──────────────────────────────────────────────────────╯
  [LAYER_RAISE] = LAYOUT(
         KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
        KC_MNXT, BP_CCED, BP_EGRV,   KC_UP,   BP_OE,   BP_AE,    BP_CIRC,  BP_DEG, BP_UGRV,   BP_AT,  BP_DLR, KC_VOLU,
        KC_MPLY,  KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT,  KC_INS,    KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,  KC_APP, KC_MUTE,
        KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, KC_PSCR,    BP_PLMN,  BP_DIV,  BP_MUL, BP_NEQL, BP_LEQL, KC_VOLD,
                                   _______, _______, QK_LLCK,    _______, _______,
                                           _______, _______,    _______
  ),

  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
  // LAYER_POINTER - Contrôle trackball + RGB + QK_BOOT/EE_CLR
  // ╰──────────────────────────────────────────────────────╯ ╰──────────────────────────────────────────────────────╯
  [LAYER_POINTER] = LAYOUT(
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,
       RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD,
       RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG,
      RGB_RMOD, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______,RGB_RMOD,
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                          XXXXXXX, KC_BTN2,    KC_BTN2
  ),
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
#        endif
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
#        endif
    }
}
#    endif

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_update_pwm_buffers(void);
#endif
