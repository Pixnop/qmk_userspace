/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * BÉPO layout - Configuration
 */
#pragma once

#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 5
#endif

#ifndef __arm__
#    define NO_ACTION_ONESHOT
#endif

#ifdef POINTING_DEVICE_ENABLE
// Auto pointer layer trigger (décommenter pour activer)
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8

// Inverse Y axis pour drag scroll (plus naturel)
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#endif

// Tapping configuration
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

// Tri-layer configuration (Lower + Raise = Adjust)
#define TRI_LAYER_LOWER_LAYER 1
#define TRI_LAYER_UPPER_LAYER 2
#define TRI_LAYER_ADJUST_LAYER 4
