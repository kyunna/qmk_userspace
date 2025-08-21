#pragma once

#include "quantum.h"

/* Layer Definitions */
enum layer_names {
    L_MAC = 0,    // MAC OS base layer: macOS-specific modifiers (Command, Option)
    L_WIN,        // Windows/Others base layer: Standard modifiers (Control, Alt, Windows)
    L_FN,         // Function layer: F-keys, Navigation, Media controls (HHKB with custom style)
    L_UTIL        // Utility layer: QK_BOOT, NK_TOGGLE, etc.
};


/* Key Definitions */
#define MAC_CAPS MT(MOD_LCTL, KC_CAPS)  // Tap for Caps Lock, hold for Control (Mac)
#define WIN_CAPS MT(MOD_LCTL, KC_LNG1)  // Tap for Language 1, hold for Control (Win)
#define SPC_FN   LT(L_FN, KC_SPC)       // Tap for Space, hold for Fn layer

/* RGB state: restores colors after timeout */
#ifdef RGBLIGHT_ENABLE
#define RGB_TIMEOUT_MS 30000
#define MAX_LED_COUNT 32
extern uint8_t last_rgb_state[MAX_LED_COUNT][3];
extern uint8_t last_rgb_mode;
extern uint8_t led_count;
#endif

/* Combo Definitions */
enum combo_events {
    CB_PAREN_OPEN,  // Sends '('
    CB_PAREN_CLOSE, // Sends ')'
    CB_UNDERSCORE,  // Sends '_'
    COMBO_LENGTH
};

/* Combo Key Mapping */
extern combo_t key_combos[COMBO_LENGTH];
