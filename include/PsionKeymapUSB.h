/*
 * PsionKeymapUSB.h
 * 
 * Psion Series 5/5mx keyboard matrix to USB HID keycode mapping
 * 
 * Maps the 8x12 key matrix to USB HID keyboard scancodes
 * Using standard USB HID Keyboard codes (HID Usage Table)
 */

#ifndef PSION_KEYMAP_USB_H
#define PSION_KEYMAP_USB_H

#include <stdint.h>
#include "board.h"

// USB HID Keyboard Keycode Values (from USB HID Specification)
// These are the raw scan codes, not the Arduino Keyboard constants

// Letters (A-Z: 0x04-0x1D)
#define HID_KEY_A          0x04
#define HID_KEY_B          0x05
#define HID_KEY_C          0x06
#define HID_KEY_D          0x07
#define HID_KEY_E          0x08
#define HID_KEY_F          0x09
#define HID_KEY_G          0x0A
#define HID_KEY_H          0x0B
#define HID_KEY_I          0x0C
#define HID_KEY_J          0x0D
#define HID_KEY_K          0x0E
#define HID_KEY_L          0x0F
#define HID_KEY_M          0x10
#define HID_KEY_N          0x11
#define HID_KEY_O          0x12
#define HID_KEY_P          0x13
#define HID_KEY_Q          0x14
#define HID_KEY_R          0x15
#define HID_KEY_S          0x16
#define HID_KEY_T          0x17
#define HID_KEY_U          0x18
#define HID_KEY_V          0x19
#define HID_KEY_W          0x1A
#define HID_KEY_X          0x1B
#define HID_KEY_Y          0x1C
#define HID_KEY_Z          0x1D

// Numbers (1-9, 0: 0x1E-0x27)
#define HID_KEY_1          0x1E
#define HID_KEY_2          0x1F
#define HID_KEY_3          0x20
#define HID_KEY_4          0x21
#define HID_KEY_5          0x22
#define HID_KEY_6          0x23
#define HID_KEY_7          0x24
#define HID_KEY_8          0x25
#define HID_KEY_9          0x26
#define HID_KEY_0          0x27

// Special keys
#define HID_KEY_ENTER      0x28
#define HID_KEY_ESC        0x29
#define HID_KEY_BACKSPACE  0x2A
#define HID_KEY_TAB        0x2B
#define HID_KEY_SPACE      0x2C
#define HID_KEY_MINUS      0x2D
#define HID_KEY_EQUAL      0x2E
#define HID_KEY_LBRACKET   0x2F
#define HID_KEY_RBRACKET   0x30
#define HID_KEY_BACKSLASH  0x31
#define HID_KEY_SEMICOLON  0x33
#define HID_KEY_QUOTE      0x34
#define HID_KEY_BACKTICK   0x35
#define HID_KEY_COMMA      0x36
#define HID_KEY_PERIOD     0x37
#define HID_KEY_SLASH      0x38

// Arrow keys
#define HID_KEY_RIGHT      0x4F
#define HID_KEY_LEFT       0x50
#define HID_KEY_DOWN       0x51
#define HID_KEY_UP         0x52

// Additional keys
#define HID_KEY_CAPS_LOCK  0x39
#define HID_KEY_SEMICOLON  0x33

// Modifier keys (used with modifier byte)
#define HID_MOD_LCTRL      0x01
#define HID_MOD_LSHIFT     0x02
#define HID_MOD_LALT       0x04
#define HID_MOD_RCTRL      0x10
#define HID_MOD_RSHIFT     0x20
#define HID_MOD_RALT       0x40

// Simplified key definitions (can be ASCII characters or HID codes)
#define KEY_A              HID_KEY_A
#define KEY_B              HID_KEY_B
#define KEY_C              HID_KEY_C
#define KEY_D              HID_KEY_D
#define KEY_E              HID_KEY_E
#define KEY_F              HID_KEY_F
#define KEY_G              HID_KEY_G
#define KEY_H              HID_KEY_H
#define KEY_I              HID_KEY_I
#define KEY_J              HID_KEY_J
#define KEY_K              HID_KEY_K
#define KEY_L              HID_KEY_L
#define KEY_M              HID_KEY_M
#define KEY_N              HID_KEY_N
#define KEY_O              HID_KEY_O
#define KEY_P              HID_KEY_P
#define KEY_Q              HID_KEY_Q
#define KEY_R              HID_KEY_R
#define KEY_S              HID_KEY_S
#define KEY_T              HID_KEY_T
#define KEY_U              HID_KEY_U
#define KEY_V              HID_KEY_V
#define KEY_W              HID_KEY_W
#define KEY_X              HID_KEY_X
#define KEY_Y              HID_KEY_Y
#define KEY_Z              HID_KEY_Z

#define KEY_0              HID_KEY_0
#define KEY_1              HID_KEY_1
#define KEY_2              HID_KEY_2
#define KEY_3              HID_KEY_3
#define KEY_4              HID_KEY_4
#define KEY_5              HID_KEY_5
#define KEY_6              HID_KEY_6
#define KEY_7              HID_KEY_7
#define KEY_8              HID_KEY_8
#define KEY_9              HID_KEY_9

// Special keys
#define KEY_ENTER          HID_KEY_ENTER
#define KEY_ESC            HID_KEY_ESC
#define KEY_BACKSPACE      HID_KEY_BACKSPACE
#define KEY_TAB            HID_KEY_TAB
#define KEY_SPACE          HID_KEY_SPACE
#define KEY_APOSTROPHE     HID_KEY_QUOTE
#define KEY_COMMA          HID_KEY_COMMA
#define KEY_PERIOD         HID_KEY_PERIOD

// Arrow keys
#define KEY_RIGHT          HID_KEY_RIGHT
#define KEY_LEFT           HID_KEY_LEFT
#define KEY_DOWN           HID_KEY_DOWN
#define KEY_UP             HID_KEY_UP

// Additional keys
#define KEY_CAPS_LOCK      HID_KEY_CAPS_LOCK
#define KEY_COLON          HID_KEY_SEMICOLON
#define KEY_DEL            HID_KEY_BACKSPACE

// Modifier keys (note: these are special and need modifier byte handling)
#define KEY_CTRL           0xE0            // HID Usage: Left Control
#define KEY_LSHIFT         0xE1            // HID Usage: Left Shift
#define KEY_RSHIFT         0xE5            // HID Usage: Right Shift
#define KEY_MENU           0xE2            // HID Usage: Left Alt
#define KEY_FN             0xE6            // HID Usage: Right Alt

// Key scancode matrix for Psion 5/5mx keyboard
// 8 rows x 12 columns
// Indexed by [row_index][col_index] where:
//   row_index: 0=ROW_01, 1=ROW_02, 2=ROW_03, 3=ROW_04, 4=ROW_05, 5=ROW_06, 6=ROW_07, 7=ROW_08
//   col_index: 0=COL_01, 1=COL_02, ..., 11=COL_12
// 0 means unmapped key (no function)
static const uint8_t keyScancode[NROWS][NCOLS] = {
  // Row 0 (ROW_01): space, up, comma, left, right, lshift
  { 0,             KEY_SPACE,    KEY_UP,        KEY_COMMA,      KEY_LEFT,      KEY_RIGHT,     KEY_LSHIFT,    0,           0,      0,        0,      0 },
  
  // Row 1 (ROW_02): z, x, c, v, b, n, rshift
  { KEY_Z,         KEY_X,        KEY_C,         KEY_V,          KEY_B,         KEY_N,         0,             KEY_RSHIFT,  0,      0,        0,      0 },
  
  // Row 2 (ROW_03): h, j, k, m, period, down, fn
  { KEY_H,         KEY_J,        KEY_K,         KEY_M,          KEY_PERIOD,    KEY_DOWN,      0,             0,           0,      0,        0,      0 },
  
  // Row 3 (ROW_04): caps, a, s, d, f, g, control
  { KEY_CAPS_LOCK, KEY_A,        KEY_S,         KEY_D,          KEY_F,         KEY_G,         0,             0,           0,      0,        0,      KEY_CTRL },
  
  // Row 4 (ROW_05): 1, 2, 3, 4, 5, 6
  { KEY_1,         KEY_2,        KEY_3,         KEY_4,          KEY_5,         KEY_6,         0,             0,           0,      0,        0,      0 },
  
  // Row 5 (ROW_06): u, i, o, p, l, enter, menu
  { KEY_U,         KEY_I,        KEY_O,         KEY_P,          KEY_L,         KEY_ENTER,     0,             0,           0,      KEY_MENU, 0,      0 },
  
  // Row 6 (ROW_07): q, w, e, r, t, y, esc
  { KEY_Q,         KEY_W,        KEY_E,         KEY_R,          KEY_T,         KEY_Y,         0,             0,           0,      0,        KEY_ESC, 0 },
  
  // Row 7 (ROW_08): 7, 8, 9, 0, del, colon
  { KEY_7,         KEY_8,        KEY_9,         KEY_0,          KEY_DEL,       KEY_COLON,     0,             0,           0,      0,        0,      0 }
};

#endif // PSION_KEYMAP_USB_H
