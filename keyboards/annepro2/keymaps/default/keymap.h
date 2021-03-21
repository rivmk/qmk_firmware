#pragma once

#include "annepro2.h"

// #define TAP_HOLD_DELAY 120
// #include "process_tap_hold.h"

enum anne_pro_layers {
  _BASE_LAYER,
  _QWERTY_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
  _EXT_LAYER,
  _EXT_SHIFT_LAYER,
  _EXT_ALT_LAYER,
  _EXT_CTRL_LAYER,
  _EMOJI_LAYER,
};

#define SFT_SPC     SFT_T(KC_SPC)
#define MT_S_UP     RSFT_T(KC_UP)
#define MT_C_RT     RCTL_T(KC_RGHT)
#define LT_FN_1     LT(_FN1_LAYER,KC_LEFT)
#define LT_FN_2     LT(_FN2_LAYER,KC_DOWN)
#define TAP_QUO     TD(TD_QUOTE)
#define TAP_DOT     TD(TD_DOT)
#define VOL_MTE     HYPR(KC_DEL)
#define VOL_DWN     HYPR(KC_PGDN)
#define VOL_UP      HYPR(KC_PGUP)
#define PAU_PLY     HYPR(KC_PAUS)
#define BT_1        KC_AP2_BT1
#define BT_2        KC_AP2_BT2
#define BT_3        KC_AP2_BT3
#define BT_4        KC_AP2_BT4
#define LED_OFF     KC_AP_LED_OFF
#define LED_ON      KC_AP_LED_ON
#define LED_DWN     KC_AP_LED_NEXT_INTENSITY
#define LED_SPD     KC_AP_LED_SPEED
#define QWERTY      TG(_QWERTY_LAYER)
#define TAP_EXT     TD(TD_EXT)
#define EXT_SFT     MO(_EXT_SHIFT_LAYER)
#define EXT_ALT     MO(_EXT_ALT_LAYER)
#define EXT_CTL     MO(_EXT_CTRL_LAYER)
#define COLON       S(KC_SCLN)

enum profile {
  RED,
  GREEN,
  BLUE,
  MIAMINIGHTS,
  RAINBOWHORIZONTAL,
  RAINBOWVERTICAL,
  ANIMATEDRAINBOWVERTICAL,
  ANIMATEDRAINBOWFLOW,
  ANIMATEDRAINBOWWATERFALL,
  ANIMATEDBREATHING,
  ANIMATEDSPECTRUM,
};

enum unicode_names {        // Commented-out emoji are implemented through macros instead
    SMILE,                  // 🙂
    GRIN,                   // 😁
    FROWN,                  // 🙁
    SAD,                    // 😔
    WINK,                   // 😉
    CRY,                    // 😭
    LAUGH,                  // 😅
    THUMBS_UP,              // 👍
    THUMBS_DOWN,            // 👎
    FIRE,                   // 🔥
    HMM,                    // 🤔
    PARTY1,                 // 🎉
    UPSIDE_DOWN,            // 🙃
    THIS,                   // 👆
    SICK,                   // 🤢
    PUKE,                   // 🤮
    GRIT,                   // 😬
    HEAD_EXPLODE,           // 🤯
    MASK,                   // 😷
    SNAKE,                  // 🐍
    EGGPLANT,               // 🍆
    _100,                   // 💯
    EYEROLL,                // 🙄
    SIREN,                  // 🚨
    MIDDLE_FINGER,          // 🖕
    FINGERS_CROSSED,        // 🤞
    TONGUE,                 // 😋
    HUG,                    // 🤗
    POOP,                   // 💩
    // DEAD,                   // 😵
    // SKULL,                  // 💀
    WUT,                    // 😳
    NO_MOUTH,               // 😶
    LOVE_EYES,              // 😍
    HEART_KISS,             // 😘
    THERM,                  // 🤒
    ROCK,                   // 🤘
    HOVA,                   // 🙌
    FIST,                   // ✊
    PRAY,                   // 🙏
    PARTY_FACE,             // 🥳
    // HEART2,                 // 💓
    KISS,                   // 😚
    CUSS,                   // 🤬
    ANGRY,                  // 😡
    SNORT,                  // 😤
    SHH,                    // 🤫
    ZIPPER,                 // 🤐
    CLAP,                   // 👏
    COOL,                   // 😎
    MONOCLE,                // 🧐
    DOWN,                   // 👇
    HAPPY_HEARTS,           // 🥰
    // COLD,                   // 🥶
    // HOT,                    // 🥵
    CAKE,                   // 🎂
    PARTY2,                 // 🎊
    BEER1,                  // 🍺
    BEER2,                  // 🍻
    BOTTLE,                 // 🍼
    // COP_CAR,                // 🚓
    JOKER,                  // 🃏
    SPEECH,                 // 💬
    THOUGHT,                // 💭
    HANDS_OUT,              // 👐
    HEAR_NO,                // 🙉
    SEE_NO,                 // 🙈
    SPEAK_NO,               // 🙊
    HAPPY_CAT,              // 😸
    LOVE_CAT,               // 😻
    SAD_CAT,                // 😿
    MUSIC1,                 // 🎵
    MUSIC2,                 // 🎶
    // VULCAN,                 // 🖖
    OH,                     // 😮
    DRUNK,                  // 🥴
    // UMM,                    // 😕
};

enum custom_keycodes {
    USA = AP2_SAFE_RANGE + 5,// 🇺🇸
    FACEPALM,                // 🤦‍♂️
    HEART,                   // ❤️
    CROSSBONES,              // ☠️
    RAISE_HAND,              // 🙋‍♂
    COFFIN,                  // ⚰
    SNOWFLAKE,               // ❄
    CHILI,                   // 🌶
    SCALES,                  // ⚖️
    BACK,                    // ⏮
    FORWARD,                 // ⏭
    PEACE,                   // ✌
    SHRUG,                   // 🤷‍♂️

    EXTEND,                  // Macro for when Ext layer is activated (sends exta key for AHK)
    EMOJI,                   // ---

    // _QK_TAP_HOLD,            // For the custom tap-hold code; needs to be last element in keycode list
};

// uint16_t QK_TAP_HOLD = _QK_TAP_HOLD;
// #define TH(n) (_QK_TAP_HOLD + n)

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
    [PARTY1]            = 0x1f389,     // 🎉
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
    // [DEAD]              = 0x1f635,     // 😵
    // [SKULL]             = 0x1f480,     // 💀
    [WUT]               = 0x1f633,     // 😳
    [NO_MOUTH]          = 0x1f636,     // 😶
    [LOVE_EYES]         = 0x1f60d,     // 😍
    [HEART_KISS]		= 0x1f618,     // 😘
    [THERM]			    = 0x1f912,     // 🤒
    [ROCK]		        = 0x1f918,     // 🤘
    [HOVA]		        = 0x1f64c,     // 🙌
    [FIST]		        = 0x0270a,     // ✊
    [PRAY]		        = 0x1f64f,     // 🙏
    [PARTY_FACE]	   	= 0x1f973,     // 🥳
    // [HEART2]		   	= 0x1f493,     // 💓
    [KISS]		        = 0x1f61a,     // 😚
    [CUSS]		        = 0x1f92c,     // 🤬
    [ANGRY]	    	  	= 0x1f621,     // 😡
    [SNORT]		        = 0x1f624,     // 😤
    [SHH]		        = 0x1f92b,     // 🤫
    [ZIPPER]		  	= 0x1f910,     // 🤐
    [CLAP]		        = 0x1f44f,     // 👏
    [COOL]		        = 0x1f60e,     // 😎
    [MONOCLE]		  	= 0x1f9d0,     // 🧐
    [DOWN]		        = 0x1f447,     // 👇
    [HAPPY_HEARTS]	  	= 0x1f970,     // 🥰
    // [COLD]		        = 0x1f976,     // 🥶
    // [HOT]		        = 0x1f975,     // 🥵
    [CAKE]		        = 0x1f382,     // 🎂
    [PARTY2]		  	= 0x1f38a,     // 🎊
    [BEER1]		        = 0x1f37a,     // 🍺
    [BEER2]		        = 0x1f37b,     // 🍻
    // [COP_CAR]		   	= 0x1f693,     // 🚓
    [JOKER]		        = 0x1f0cf,     // 🃏
    [SPEECH]		   	= 0x1f4ac,     // 💬
    [THOUGHT]		   	= 0x1f4ad,     // 💭
    [HANDS_OUT]		   	= 0x1f450,     // 👐
    [HEAR_NO]		   	= 0x1f649,     // 🙉
    [SEE_NO]		   	= 0x1f648,     // 🙈
    [SPEAK_NO]		   	= 0x1f64a,     // 🙊
    [HAPPY_CAT]		   	= 0x1f638,     // 😸
    [LOVE_CAT]		   	= 0x1f63b,     // 😻
    [SAD_CAT]		   	= 0x1f63f,     // 😿
    [MUSIC1]		   	= 0x1f3b5,     // 🎵
    [MUSIC2]		   	= 0x1f3b6,     // 🎶
    // [VULCAN]		    = 0x1f596,     // 🖖
    [OH]			    = 0x1f62e,     // 😮
    [DRUNK]			    = 0x1f974,     // 🥴
    // [UMM]			    = 0x1f615,     // 😕
};

// Tap Dance Stuff
enum {
  TD_QUOTE = 0,
  TD_DOT,
  TD_EXT,
};
