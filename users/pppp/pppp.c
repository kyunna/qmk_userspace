#include QMK_KEYBOARD_H
#include "pppp.h"
#include "timer.h"

/* Detects the host OS and sets the default layer accordingly. */
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            default_layer_set(1UL << L_MAC);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
        default:
            default_layer_set(1UL << L_WIN);
            break;
    }

    return true;
}

#ifdef RGBLIGHT_ENABLE
static uint32_t last_activity = 0;
static bool rgb_off_due_to_timeout = false;

uint8_t last_rgb_state[MAX_LED_COUNT][3] = {0};
uint8_t last_rgb_mode = 0;
uint8_t led_count = 0;

/*
 * RGB lighting timeout and restore handlers.
 *
 * These functions manage RGB timeout after inactivity,
 * turn off RGB lighting when the timeout expires, and
 * restore the previous RGB state when key input is detected.
 */

void restore_rgb_state(void) {
    if (led_count == 0 || last_rgb_mode == 0) {
        return; // Nothing to restore
    }

    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(last_rgb_mode);

    for (int i = 0; i < led_count; i++) {
        rgblight_setrgb_at(
            last_rgb_state[i][0],
            last_rgb_state[i][1],
            last_rgb_state[i][2],
            i
        );
    }
}

void housekeeping_task_user(void) {
    if (!rgb_off_due_to_timeout &&
            timer_elapsed32(last_activity) > RGB_TIMEOUT_MS) {
        rgblight_disable_noeeprom();
        rgb_off_due_to_timeout = true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_activity = timer_read32();

        if (rgb_off_due_to_timeout) {
            restore_rgb_state();
            rgb_off_due_to_timeout = false;
        }
    }

    return true;
}
#endif

/*Customize TAPPING_TERM for specific keys. */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC_CAPS:
        case WIN_CAPS:
            // CAPS position MT key: much shorter tapping term for quick Ctrl combos
            return 125;

        case SPC_FN:
            // SPACE position LT key: slightly shorter tapping term for reliable tapping
            return 150;

        default:
            // Default tapping term for all other keys
            return TAPPING_TERM;
    }
}

/* Flow Tap customization for our specific keys */
bool is_flow_tap_key(uint16_t keycode) {
    /* Disable Flow Tap when modifiers are already active (hotkey prevention) */
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false;
    }

    switch (get_tap_keycode(keycode)) {
        case KC_SPC:        // For SPC_FN
        case KC_CAPS:       // For MAC_CAPS
        case KC_LNG1:       // For WIN_CAPS
        case KC_A ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }
    return false;
}

/* Per-key Flow Tap timing optimization */
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {
    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        switch (keycode) {
            case MAC_CAPS:
            case WIN_CAPS:
                return FLOW_TAP_TERM - 25;  // 100ms - CAPS: faster Ctrl access

            case SPC_FN:
                return FLOW_TAP_TERM + 25;  // 150ms - SPACE: safer typing flow

            default:
                return FLOW_TAP_TERM;       // 125ms - Default for other keys
        }
    }
    return 0;  // Disable Flow Tap
}

/* Defines combo keys (pressing two keys at once produces a third key). */
const uint16_t PROGMEM df_combo[]  = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[]  = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[]  = {KC_K, KC_L, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    [CB_PAREN_OPEN]   = COMBO(df_combo,  KC_LPRN),
    [CB_PAREN_CLOSE]  = COMBO(jk_combo,  KC_RPRN),
    [CB_UNDERSCORE]   = COMBO(kl_combo,  KC_UNDS),
};
