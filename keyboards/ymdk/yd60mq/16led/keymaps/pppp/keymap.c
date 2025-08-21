#include QMK_KEYBOARD_H
#include "keymap.h"
#include "keymaps/keymap_60_hhkb.h"

#ifdef RGBLIGHT_ENABLE
/* Initial RGB configuration: number of LEDs and startup mode. */
#define LED_COUNT 16
#define INITIAL_RGB_MODE RGBLIGHT_MODE_STATIC_LIGHT

/* Default backplate color (Light greenish) */
#define RGB_R 144
#define RGB_G 238
#define RGB_B 144

/* Apply and save RGB color to all LEDs. */
void set_rgb(void) {
    led_count = (LED_COUNT > MAX_LED_COUNT) ? MAX_LED_COUNT : LED_COUNT;

    for (int i = 0; i < led_count; i++) {
        rgblight_setrgb_at(RGB_R, RGB_G, RGB_B, i);

        last_rgb_state[i][0] = RGB_R;
        last_rgb_state[i][1] = RGB_G;
        last_rgb_state[i][2] = RGB_B;
    }

    last_rgb_mode = INITIAL_RGB_MODE;
}

/* Called once after keyboard initializes. */
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(INITIAL_RGB_MODE);
    set_rgb();
}
#endif
