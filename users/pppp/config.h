#pragma once

/* QMK behavior configuration */
#define TAPPING_TERM 150 // Tap-hold decision time (ms)
#define TAPPING_TERM_PER_KEY // Enable different TAPPING_TERM for specific keys
#define COMBO_TERM 30  // Time window to press combos (ms)
#define PERMISSIVE_HOLD // Allow hold if other key is pressed during tap
#define FLOW_TAP_TERM 125 // Prevent accidental mods during typing
