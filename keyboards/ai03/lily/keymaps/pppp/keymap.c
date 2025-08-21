#include QMK_KEYBOARD_H
#include "keymap.h"
#include "keymaps/keymap_60_hhkb.h"

#ifdef RGBLIGHT_ENABLE
/* Initial RGB configuration: number of LEDs and startup mode. */
#define LED_COUNT 3
#define INITIAL_RGB_MODE RGBLIGHT_MODE_STATIC_LIGHT

/* Default colors for MAC/WIN layers */
const uint8_t MAIN_COLOR[LED_COUNT][3] = {
    {186, 85, 211},   // Medium Orchid
    {148, 0, 211},    // Dark Violet
    {138, 43, 226}    // Blue Violet
};

/* FN layer colors (cooler tone) */
const uint8_t FN_COLOR[LED_COUNT][3] = {
    {72, 61, 139},    // Dark Slate Blue
    {123, 104, 238},  // Medium Slate Blue
    {106, 90, 205}    // Slate Blue
};

/* UTIL layer colors (darker tone) */
const uint8_t UTIL_COLOR[LED_COUNT][3] = {
    {75, 0, 130},     // Indigo
    {54, 0, 100},     // Deep Purple
    {46, 0, 85}       // Very dark purple
};

/* Apply and save RGB colors. */
void set_rgb(const uint8_t colors[LED_COUNT][3], uint8_t mode) {
    led_count = (LED_COUNT > MAX_LED_COUNT) ? MAX_LED_COUNT : LED_COUNT;

    for (int i = 0; i < led_count; i++) {
        rgblight_setrgb_at(colors[i][0], colors[i][1], colors[i][2], i);

        last_rgb_state[i][0] = colors[i][0];
        last_rgb_state[i][1] = colors[i][1];
        last_rgb_state[i][2] = colors[i][2];
    }

    last_rgb_mode = mode;
}

/* Called once after keyboard initializes. */
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(INITIAL_RGB_MODE);
    set_rgb(MAIN_COLOR, INITIAL_RGB_MODE);
}

/* Called when active layer changes (FN/UTIL). */
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    switch (layer) {
        case L_FN:
            set_rgb(FN_COLOR, INITIAL_RGB_MODE);
            break;
        case L_UTIL:
            set_rgb(UTIL_COLOR, INITIAL_RGB_MODE);
            break;
        default:
            set_rgb(MAIN_COLOR, INITIAL_RGB_MODE);
            break;
    }

    return state;
}
#endif
