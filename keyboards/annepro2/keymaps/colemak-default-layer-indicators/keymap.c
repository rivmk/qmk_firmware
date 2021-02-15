#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 10    // in seconds
static uint16_t idle_timer = 0;
static uint8_t second_counter = 0;
static bool qwerty = false;
static bool caps = false;

enum anne_pro_layers {
  _BASE_LAYER,
  _QWERTY_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
  _EMOJI_LAYER,
};

enum profile {
  RED,
  GREEN,
  BLUE,
  RAINBOWHORIZONTAL,
  RAINBOWVERTICAL,
  ANIMATEDRAINBOWVERTICAL,
  ANIMATEDRAINBOWFLOW,
  ANIMATEDRAINBOWWATERFALL,
  ANIMATEDBREATHING,
  ANIMATEDSPECTRUM,
};

enum unicode_names {
  SMILE,                // 🙂
  GRIN,                 // 😁
  FROWN,                // 🙁
  SAD,                  // 😔
  WINK,                 // 😉
  CRY,                  // 😭
  LAUGH,                // 😅
  THUMBS_UP,            // 👍
  THUMBS_DOWN,          // 👎
  FIRE,                 // 🔥
  HMM,                  // 🤔
  PARTY,                // 🎉
  UPSIDE_DOWN,          // 🙃
  THIS,                 // 👆
  SICK,                 // 🤢
  PUKE,                 // 🤮
  GRIT,                 // 😬
  HEAD_EXPLODE,         // 🤯
  MASK,                 // 😷
  SNAKE,                // 🐍
  EGGPLANT,             // 🍆
  _100,                 // 💯
  EYEROLL,              // 🙄
  SIREN,                // 🚨
  MIDDLE_FINGER,        // 🖕
  FINGERS_CROSSED,      // 🤞
  TONGUE,               // 😋
  HUG,                  // 🤗
  POOP,                 // 💩
  DEAD,                 // 😵
  SKULL,                // 💀
  WUT,                  // 😳
  NO_MOUTH,             // 😶
};

enum custom_keycodes {
  USA = AP2_SAFE_RANGE, // 🇺🇸
  FACEPALM,             // 🤦‍♂️
  HEART,                // ❤️
  CROSSBONES,           // ☠️
};

const uint32_t PROGMEM unicode_map[] = {      // see https://cryptii.com/pipes/unicode-lookup
  [SMILE]             = 0x1f642,     // 🙂
  [GRIN]              = 0x1f601,     // 😁
  [FROWN]             = 0x1f641,     // 🙁
  [SAD]               = 0x1f614,     // 😔
  [WINK]              = 0x1f609,     // 😉
  [CRY]               = 0x1f62d,     // 😭
  [LAUGH]             = 0x1f605,     // 😅
  [THUMBS_UP]         = 0x1f44d,     // 👍
  [THUMBS_DOWN]       = 0x1f44e,     // 👎
  [FIRE]              = 0x1f525,     // 🔥
  [HMM]               = 0x1f914,     // 🤔
  [PARTY]             = 0x1f389,     // 🎉
  [UPSIDE_DOWN]       = 0x1f643,     // 🙃
  [THIS]              = 0x1f446,     // 👆
  [SICK]              = 0x1f922,     // 🤢
  [PUKE]              = 0x1f92e,     // 🤮
  [GRIT]              = 0x1f62c,     // 😬
  [HEAD_EXPLODE]      = 0x1f92f,     // 🤯
  [MASK]              = 0x1f637,     // 😷
  [SNAKE]             = 0x1f40d,     // 🐍
  [EGGPLANT]          = 0x1f346,     // 🍆
  [_100]              = 0x1f4af,     // 💯
  [EYEROLL]           = 0x1f644,     // 🙄
  [SIREN]             = 0x1f6a8,     // 🚨
  [MIDDLE_FINGER]     = 0x1f595,     // 🖕
  [FINGERS_CROSSED]   = 0x1f91e,     // 🤞
  [TONGUE]            = 0x1f60b,     // 😋
  [HUG]               = 0x1f917,     // 🤗
  [POOP]              = 0x1f4a9,     // 💩
  [DEAD]              = 0x1f635,     // 😵
  [SKULL]             = 0x1f480,     // 💀
  [WUT]               = 0x1f633,     // 😳
  [NO_MOUTH]          = 0x1f636,     // 😶
};

// The function to handle the caps lock logic
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    // Set the leds to red
    annepro2LedSetForegroundColor(0xFF, 0x00, 0x00);
    caps = true;
  } else {
    caps = false;
    // Reset back to the current profile if there is no layer active
    if(!layer_state_is(_FN1_LAYER) && !layer_state_is(_FN2_LAYER) && !layer_state_is(_QWERTY_LAYER)) {
      annepro2LedResetForegroundColor();
    }
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
            case USA:
                send_unicode_string("🇺🇸");
                return false;
            case FACEPALM:
                send_unicode_string("🤦‍♂️");
                return false;
            case HEART:
                send_unicode_string("❤️");
                return false;
            case CROSSBONES:
                send_unicode_string("☠️");
                return false;
        }
    }
    return true;
};

// Tap Dance Stuff
enum {
  TD_QUOTE = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT,KC_DQUO)
};

// void dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         register_code(KC_QUOT);
//     } else {
//         register_code16(KC_DQUO);
//     }
// }

// void dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         unregister_code(KC_QUOT);
//     } else {
//         unregister_code16(KC_DQUO);
//     }
// }

// qk_tap_dance_action_t tap_dance_actions[] = {
//     [TD_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_quote_finished, dance_quote_reset),
// };

// Key symbols are based on QMK. Use them to remap your keyboard
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* COLEMAK-DH LAYER
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  f  |  p  |  b  |  j  |  l  |  u  |  y  |  ;  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Caps    |  a  |  r  |  s  |  t  |  g  |  m  |  n  |  e  |  i  |  o  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  x  |  c  |  d  |  v  |  z  |  k  |  h  |  ,  |  .  |  /  |    Shift       |
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
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, TD(TD_QUOTE), KC_ENT,              // consider replacing KC_QUOT with TD(TD_QUOTE);
    KC_LSFT, KC_X, KC_C, KC_D, KC_V, KC_Z, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, LT(_FN1_LAYER,KC_LEFT), LT(_FN2_LAYER,KC_DOWN), RCTL_T(KC_RGHT)
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
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, TD(TD_QUOTE), KC_ENT,         // consider replacing KC_QUOT with TD(TD_QUOTE);
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, LT(_FN1_LAYER,KC_LEFT), LT(_FN2_LAYER,KC_DOWN), RCTL_T(KC_RGHT)
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
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    _______, _______, KC_UP, _______, _______, _______, _______, _______, KC_UP, _______, KC_PSCR, KC_HOME, KC_END, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGUP, KC_PGDN, _______,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPLY, _______, _______, _______, KC_INS, KC_DEL, _______,
    C(S(G(KC_DEL))), C(S(G(KC_PGDN))), C(S(G(KC_PGUP))), C(S(G(KC_PAUS))), _______, _______, MO(_EMOJI_LAYER), _______          // The weird keycodes are to trigger media controls through AHK until the bug gets fixed
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
    KC_SLEP, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, _______, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, TG(_QWERTY_LAYER),
    _______, _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_HOME, KC_END, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPLY, _______, _______, _______, KC_INS, KC_DEL, _______,
    C(S(G(KC_DEL))), C(S(G(KC_PGDN))), C(S(G(KC_PGUP))), C(S(G(KC_PAUS))), _______, MO(_EMOJI_LAYER), _______, _______      // The weird keycodes are to trigger media controls through AHK until the bug gets fixed
 ),
/*
  * Layer _EMOJI_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |SLEEP| BT1 | BT2 | BT3 | BT4 |     |     |     |     |LEDOF|LEDON|LDNXT|LDSPD|  QWERTY   |
  * |-----------------------------------------------------------------------------------------+
  * |        |     | UP  |     |     |     |     |     | UP  |     | PS | HOME | END |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |LEFT |DOWN |RIGHT|     |     |     |LEFT |DOWN |RIGHT|PGUP |PGDN |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |INSRT| DEL |                |
  * |-----------------------------------------------------------------------------------------+
  * | MUTE  | V-DWN | V-UP  |             PLAY_PAUSE          |       |  Fn1  |  Fn2  |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_EMOJI_LAYER] = KEYMAP(
    _______, X(_100), X(POOP), HEART, X(MASK), XP(SNAKE, EGGPLANT), CROSSBONES, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, XP(WINK, TONGUE), X(FIRE), XP(PARTY, SIREN), _______, _______, _______, USA, _______, _______, _______, _______, _______,
    _______, _______, XP(SICK, PUKE), XP(SMILE, GRIN), XP(THUMBS_UP, THUMBS_DOWN), XP(THIS, FINGERS_CROSSED), X(MIDDLE_FINGER), _______, XP(EYEROLL, HEAD_EXPLODE), _______, _______, _______, _______,
    _______, XP(DEAD, SKULL), XP(CRY, GRIT), XP(FROWN, SAD), _______, _______, FACEPALM, X(HUG), _______, XP(WUT, NO_MOUTH), XP(HMM, UPSIDE_DOWN), _______,
    _______, _______, _______, _______, _______, _______, _______, _______
 ),
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {
}

void matrix_scan_user(void) {    // remember to keep this function even if I remove the timeout code
  // idle_timer needs to be set one time
    if (idle_timer == 0) idle_timer = timer_read();

    if (timer_elapsed(idle_timer) > 1000) {
        second_counter++;
        idle_timer = timer_read();
    }
    if (second_counter >= BACKLIGHT_TIMEOUT) {
        annepro2LedDisable();
        second_counter = 0;
    }
};

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    // Here are two common functions that you can use. For more LED functions, refer to the file "qmk_ap2_led.h"

    // annepro2-shine disables LEDs by default. Uncomment this function to enable them at startup.
    annepro2LedEnable();

    // Additionally, it also chooses the first LED profile by default. Refer to the "profiles" array in main.c in
    // annepro2-shine to see the order. Replace "i" with the index of your preferred profile. (i.e the RED profile is index 0)
    annepro2LedSetProfile(3);
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

// This is some code that might be used to make the caps lock light work better with EPKL
  // if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)){
  //     #ifdef AUDIO_ENABLE
  // 	    PLAY_SONG(tone_caps_off);
  //     #endif
  // } else {
  // 	#ifdef AUDIO_ENABLE
  // 		PLAY_SONG(tone_caps_on);
	// #endif
