/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * BÉPO layout - Configuration
 */
#pragma once

#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif

#ifndef __arm__
#    define NO_ACTION_ONESHOT
#endif

#ifdef POINTING_DEVICE_ENABLE
// Auto pointer layer trigger (décommenter pour activer)
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif
