/*=============================================
                      TODO

    • Might want to simplify the extend macros--maybe tie F22 to when *layer* is activated/de-activated?
=============================================*/

#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "keymap.h"             // Custom Keycodes, unicode, macros, etc. are in keymap.h


// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 10    // in seconds
static uint16_t idle_timer = 0;
static uint8_t second_counter = 0;
static bool qwerty = false;
static bool caps = false;

// Trackers for the help images
static bool f21_tracker = false;
static bool f22_tracker = false;

// Apparently needed for the shift+Backspace = Del code
uint8_t mod_state;

 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*
  * EMPTY KEYBOARD TEMPLATE
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |    |      |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  *
  * [_LAYER] = KEYMAP(
  * _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  * _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  * _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  * _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  * _______, _______, _______,                   _______,                   _______, _______, _______, _______
  * ),
  */



  /* COLEMAK-DH (BASE) LAYER
  * Layer _BASE_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  f  |  p  |  b  |  [  |  j  |  l  |  u  |  y  |  '  |  ;  |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Caps    |  a  |  r  |  s  |  t  |  g  |  ]  |  m  |  n  |  e  |  i  |  o  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  x  |  c  |  d  |  v  |  z  |  /  |  k  |  h  |  ,  |  .  |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  * Layer TAP in _BASE_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |       UP       |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
  * \-----------------------------------------------------------------------------------------/
  */
 [_BASE_LAYER] = KEYMAP(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC, KC_J,    KC_L,    KC_U,    KC_Y,    TAP_QUO, KC_SCLN, KC_BSLS,
    EXTEND1, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_RBRC, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LSFT, KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,    KC_SLSH, KC_K,    KC_H,    KC_COMM, TAP_DOT, MT_S_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                   SFT_SPC,                   KC_F23,  LT_FN_1, LT_FN_2, MT_C_RT
),

  /*
  * Layer _QWERTY_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Caps    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  * Layer TAP in _QWERTY_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |       UP       |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
  * \-----------------------------------------------------------------------------------------/
  */
 [_QWERTY_LAYER] = KEYMAP(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    TAP_EXT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, TAP_QUO, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, TAP_DOT, KC_SLSH, MT_S_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                   SFT_SPC,                   KC_F23,  LT_FN_1, LT_FN_2, MT_C_RT
),

  /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * |        |     | UP  |     |     |     |     |     | UP  |     | PS | HOME | END |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |LEFT |DOWN |RIGHT|     |     |     |LEFT |DOWN |RIGHT| PGUP|PGDN |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |INSRT| DEL |                |
  * |-----------------------------------------------------------------------------------------+
  * | MUTE  | V-DWN | V-UP  |             PLAY_PAUSE          |       |       | EMOJI |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, KC_UP,   _______, KC_PSCR, KC_HOME, KC_END,  _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN, _______,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPLY, _______, _______, _______, KC_INS,  KC_DEL,  _______,
    VOL_MTE, VOL_DWN, VOL_UP,                    PAU_PLY,                   _______, _______, EMOJI,   _______          // If the media bug gets fixed, change to regular media keycodes
),

  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |SLEEP| BT1 | BT2 | BT3 | BT4 |     |     |     |     |LEDOF|LEDON|LDNXT|LDSPD|  QWERTY   |
  * |-----------------------------------------------------------------------------------------+
  * |        |     | UP  |     |     |     |     |     | UP  |     | PS | HOME | END |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |LEFT |DOWN |RIGHT|     |     |     |LEFT |DOWN |RIGHT| PGUP|PGDN |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |INSRT| DEL |                |
  * |-----------------------------------------------------------------------------------------+
  * | MUTE  | V-DWN | V-UP  |             PLAY_PAUSE          |       | EMOJI |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP(
    KC_SLEP, BT_1,    BT_2,    BT_3,    BT_4,    _______, _______, _______, _______, LED_OFF, LED_ON,  LED_DWN, LED_SPD, QWERTY,
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_HOME, KC_END,  _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPLY, _______, _______, _______, KC_INS,  KC_DEL,  _______,
    VOL_MTE, VOL_DWN, VOL_UP,                    PAU_PLY,                   _______, EMOJI,   _______, _______          // If the media bug gets fixed, change to regular media keycodes
 ),

  /*
  * Layer _EXT_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |    |      |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_EXT_LAYER] = KEYMAP(
    KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    KC_BSPC, KC_DEL,  KC_WH_U, KC_WBAK, KC_WFWD, KC_MS_U, KC_ESC,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_APP,  KC_ESC,
    _______, KC_LALT, KC_WH_D, KC_LSFT, KC_LCTL, KC_MS_D, KC_INS,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______,
    EXT_SFT, C(KC_X), C(KC_C), KC_BTN3, C(KC_V), C(KC_Z), KC_WH_R, KC_BTN1, KC_BTN2, KC_MS_L, KC_MS_R, EXT_SFT,
    EXT_CTL, _______, EXT_ALT,                   PAU_PLY,                   EXT_ALT, _______, _______, EXT_CTL
 ),

  /*
  * Layer _EXT_SHIFT_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |    |      |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_EXT_SHIFT_LAYER] = KEYMAP(
    KC_ESC,  S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), KC_PEQL, KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, KC_PMNS, KC_BSPC,
    KC_TAB,  KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_ESC,  S(KC_9), KC_PGUP, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_QUOT, KC_COMM,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_NLCK, S(KC_0), KC_PGDN, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
    _______, C(KC_X), C(KC_C), KC_BTN2, C(KC_V), C(KC_Z), KC_PSLS, COLON,   KC_KP_0, KC_KP_0, KC_PDOT, _______,
    EXT_CTL, _______, EXT_ALT,                   SFT_SPC,                   EXT_ALT, _______, _______, EXT_CTL
 ),

  /*
  * Layer _EXT_ALT_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |    |      |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_EXT_ALT_LAYER] = KEYMAP(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                   _______,                   _______, _______, _______, _______
 ),

  /*
  * Layer _EXT_CTRL_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |    |      |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_EXT_CTRL_LAYER] = KEYMAP(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                   _______,                   _______, _______, _______, _______
 ),

/*
  * Layer _EMOJI_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |💯👏|💩🤬|❤️💓|😷🤒|🐍🍆|💀☠️|🥶❄️|🥵🌶️|🙈😸 |🙉😻|🙊😿 |🎵🎶|          |
  * |-----------------------------------------------------------------------------------------+
  * |        |🤫🤐|😉😋|🤦‍♂️🙋‍♂️|🎉🎊|🍺🍻|🤗👐|⚖️🃏 |😍🥰|🇺🇸🚓|🤢🤮|💬💭 |⏮️⏭️ |       |
  * |-----------------------------------------------------------------------------------------+
  * |         |😡😤|🔥🚨 |🙂😁|👍👎 |😎🧐|🥳🎂|🖕🤘 |👆👇 |🙄🤯 |🙌✊ |😮🥴|            |
  * |-----------------------------------------------------------------------------------------+
  * |   SHIFT    |😵⚰️|😭😬|🙁😔|✌️🖖 |🤞🙏 |🤷‍♂️😕 |😘😚|🤔🙃|😳😶|EmjPk|    SHIFT      |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |          SPACE/SHIFT            |       | EMOJI | EMOJI |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_EMOJI_LAYER] = KEYMAP(
    KC_ESC, XP(_100, CLAP), XP(POOP, CUSS), HEART, XP(MASK, THERM), XP(SNAKE, EGGPLANT), CROSSBONES, SNOWFLAKE, CHILI, XP(SEE_NO, HAPPY_CAT), XP(HEAR_NO, LOVE_CAT), XP(SPEAK_NO, SAD_CAT), XP(MUSIC1, MUSIC2), KC_BSPC,
    _______, XP(SHH, ZIPPER), XP(WINK, TONGUE), FACEPALM, XP(PARTY1, PARTY2), XP(BEER1, BEER2), XP(HUG, HANDS_OUT), SCALES, XP(LOVE_EYES, HAPPY_HEARTS), USA, XP(SICK, PUKE), XP(SPEECH, THOUGHT), BACK, _______,
    _______, XP(ANGRY, SNORT), XP(FIRE, SIREN), XP(SMILE, GRIN), XP(THUMBS_UP, THUMBS_DOWN), XP(COOL, MONOCLE), XP(PARTY_FACE, CAKE), XP(MIDDLE_FINGER, ROCK), XP(THIS, DOWN), XP(OH, DRUNK), XP(EYEROLL, HEAD_EXPLODE), XP(HOVA, FIST), _______,
    KC_LSFT, COFFIN, XP(CRY, GRIT), XP(FROWN, SAD), PEACE, XP(FINGERS_CROSSED, PRAY), SHRUG, XP(HEART_KISS, KISS), XP(HMM, UPSIDE_DOWN), XP(WUT, NO_MOUTH), G(KC_DOT), KC_RSFT,
    _______, _______, _______, SFT_SPC, _______, EMOJI, EMOJI, _______
 ),
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    if (idle_timer == 0) idle_timer = timer_read();         // idle_timer needs to be set one time

    if (timer_elapsed(idle_timer) > 1000) {
        second_counter++;
        idle_timer = timer_read();
    }
    if (second_counter >= BACKLIGHT_TIMEOUT) {
        annepro2LedDisable();
        second_counter = 0;
    }

    // matrix_scan_tap_hold();                                 // For the custom tap-hold code
};

// The function to handle the caps lock logic
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    annepro2LedSetForegroundColor(0xFF, 0x00, 0x00);        // Set the leds to red
    caps = true;
  } else {
    caps = false;
    if(!layer_state_is(_FN1_LAYER) && !layer_state_is(_FN2_LAYER) && !layer_state_is(_QWERTY_LAYER)) {
      annepro2LedResetForegroundColor();                    // Reset back to the current profile if there is no layer active
    }
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();                         // This is for the Shift+Backspace → Del code that I stole

    // process_record_tap_hold(keycode, record);       // For the custom tap-hold code
    //    return true;

    if (record->event.pressed) {
        // LED Timeout Code
        if (caps) {
            annepro2LedEnable();
            annepro2LedSetForegroundColor(0xFF, 0x00, 0x00);
        } else if (qwerty) {
            annepro2LedEnable();
            annepro2LedSetForegroundColor(0x00, 0x00, 0xFF);
        } else {
            annepro2LedEnable();
        }
        idle_timer = timer_read();
        second_counter = 0;

        // Multi-character emoji macros
        switch (keycode) {

            // Emoji macros
            case USA:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("🇺🇸");       // Default
                } else {
                    send_unicode_string("🚓");      // If shifted
                }
                return false;

            case FACEPALM:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("🤦‍♂️");      // Default
                } else {
                    send_unicode_string("🙋‍♂️");      // If shifted
                }
                return false;

            case HEART:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("❤️");      // Default
                } else {
                    send_unicode_string("💓");      // If shifted
                }
                return false;

            case CROSSBONES:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("💀");      // Default
                } else {
                    send_unicode_string("☠️");      // If shifted
                }
                return false;

            // case RAISE_HAND:                        // Unneeded because raise hand is in the facepalm macro
            //     if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
            //         send_unicode_string("🙋‍♂️");      // Default
            //     } else {
            //         send_unicode_string("");        // If shifted
            //     }
            //     return false;

            case COFFIN:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("😵");      // Default
                } else {
                    send_unicode_string("⚰️");      // If shifted
                }
                return false;

            case SNOWFLAKE:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("🥶");      // Default
                } else {
                    send_unicode_string("❄️");      // If shifted
                }
                return false;

            case CHILI:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("🥵");      // Default
                } else {
                    send_unicode_string("🌶️");      // If shifted
                }
                return false;

            case BACK:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("⏮️");      // Default
                } else {
                    send_unicode_string("⏭️");      // If shifted
                }
                return false;

            // case FORWARD:
            //     if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
            //         send_unicode_string("⏭️");      // Default
            //     } else {
            //         send_unicode_string("");      // If shifted
            //     }
            //     return false;

            case PEACE:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("✌️");      // Default
                } else {
                    send_unicode_string("🖖");      // If shifted
                }
                return false;

            case SHRUG:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("🤷‍♂️");      // Default
                } else {
                    send_unicode_string("😕");      // If shifted
                }
                return false;

            case SCALES:
                if (!(get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))) {
                    send_unicode_string("⚖️");      // Default
                } else {
                    send_unicode_string("🃏");      // If shifted
                }
                return false;


            // Extend Layer selector macro (sends an additional key signal for AHK purposes)
            // TODO: Find some way to make this toggle-able (and also to work with the image script. Maybe send a diff Fn keycode when toggled?)
            case EXTEND1:
                if (record->event.pressed) {
                    layer_invert(_EXT_LAYER);
                    register_code(KC_F22);              // Holds down F22 (for AHK image script)
                    f22_tracker = true;
                }
                break;                                  // Second part (when key is released) is in post_process below
            // case EXTEND2:
            //     if (record->event.pressed) {
            //         if (!f22_tracker) {
            //             layer_invert(_EXT_LAYER);       // Turn on the Ext layer when just tapped
            //             register_code(KC_F22);          // Hold down F22 until Ext is tapped again
            //             f22_tracker = true;
            //         } else {
            //             unregister_code(KC_F22);        // Release F22
            //             layer_invert(_EXT_LAYER);       // Turns off the extend layer
            //             f22_tracker = false;
            //         }
            //     }
            //     break;

            // Emoji Layer selector macro (sends an additional key signal for AHK purposes)
            case EMOJI:
                if (record->event.pressed) {
                    layer_invert(_EMOJI_LAYER);
                    register_code(KC_F21);              // Holds down F21 (for AHK image script)
                    f21_tracker = true;
                }
                break;                                  // Second part (when key is released) is in post_process below

            // Stolen code that turns Shift+Backspace → Delete
            case KC_BSPC:
            {
                static bool delkey_registered;
                if (record->event.pressed) {
                    if (mod_state & MOD_MASK_SHIFT) {
                        // In case only one shift is held
                        // see https://stackoverflow.com/questions/1596668/logical-xor-operator-in-c
                        // This also means that in case of holding both shifts and pressing KC_BSPC,
                        // Shift+Delete is sent (useful in Firefox) since the shift modifiers aren't deleted.
                        if (!(mod_state & MOD_BIT(KC_LSHIFT)) != !(mod_state & MOD_BIT(KC_RSHIFT))) {
                            del_mods(MOD_MASK_SHIFT);
                        }
                        register_code(KC_DEL);
                        delkey_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else {
                    if (delkey_registered) {
                        unregister_code(KC_DEL);
                        delkey_registered = false;
                        return false;
                    }
                }
                return true;
            }

        break;

        }
    }
    return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EXTEND1:                           // For when Ext is released after being held
      if (!record->event.pressed) {
        f22_tracker = false;
        if (!f22_tracker) {
            unregister_code(KC_F22);        // Releases F22
            layer_invert(_EXT_LAYER);       // Turns off the extend layer
        }
      }
      break;

    case EMOJI:
      if (!record->event.pressed) {
        f21_tracker = false;
        if (!f21_tracker) {
            unregister_code(KC_F21);        // Releases F21
            layer_invert(_EMOJI_LAYER);     // Turns off the emoji layer
        }
      }
      break;
  }
}

void sentence_end(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {

        // Double tapping TD_DOT produces
        // ". <one-shot-shift>" i.e. dot, space and capitalize next letter.
        // This helps to quickly end a sentence and begin another one
        // without having to hit shift.
        case 2:
            /* Check that Shift is inactive */
            if (!(get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_SPC);
                /* Internal code of OSM(MOD_LSFT) */
                add_oneshot_mods(MOD_BIT(KC_LSHIFT));

            } else {
                // send ">" (KC_DOT + shift → ">")
                tap_code(KC_DOT);
            }
            break;

        // Since `sentence_end` is called on each tap
        // and not at the end of the tapping term,
        // the third tap needs to cancel the effects
        // of the double tap in order to get the expected
        // three dots ellipsis.
        case 3:
            // remove the added space of the double tap case
            tap_code(KC_BSPC);
            // replace the space with a second dot
            tap_code(KC_DOT);
            // tap the third dot
            tap_code(KC_DOT);
            break;

        // send KC_DOT on every normal tap of TD_DOT
        default:
            tap_code(KC_DOT);
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT,KC_DQUO),
  [TD_EXT] = ACTION_TAP_DANCE_DOUBLE(EXTEND1, EXTEND2),
  [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(sentence_end, NULL, NULL),
};

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

// Tap-hold actions (not working right now); available macros are:
//      ACTION_TAP_HOLD_SHIFT(KC_TAP, KC_HOLD, KC_TAP_SHIFT, KC_HOLD_SHIFT)
//      ACTION_TAP_HOLD(KC_TAP, KC_HOLD)
                // tap_hold_action_t tap_hold_actions[] = {
                // [0] = ACTION_TAP_HOLD(EXTEND1, EXTEND2),
                // [1] = ACTION_TAP_HOLD(KC_A, KC_B),
                // };

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    // Here are two common functions that you can use. For more LED functions, refer to the file "qmk_ap2_led.h"

    // annepro2-shine disables LEDs by default. Uncomment this function to enable them at startup.
    annepro2LedEnable();

    // Additionally, it also chooses the first LED profile by default. Refer to the "profiles" array in main.c in
    // annepro2-shine to see the order. Replace "i" with the index of your preferred profile. (i.e the RED profile is index 0)
    annepro2LedSetProfile(4);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
  switch(get_highest_layer(layer)) {
    // case _FN1_LAYER:
    //   // Set the leds to green
    //   annepro2LedSetForegroundColor(0x00, 0xFF, 0x00);
    //   break;
    // case _FN2_LAYER:
    //   // Set the leds to blue
    //   annepro2LedSetForegroundColor(0x00, 0x00, 0xFF);
    //   break;
    case _QWERTY_LAYER:
      // Set the leds to blue
      annepro2LedSetForegroundColor(0x00, 0x00, 0xFF);
      qwerty = true;
      break;
    default:
      // Reset back to the current profile
      annepro2LedResetForegroundColor();
      qwerty = false;
      break;
  }
  return layer;
}
