//
// Created by Henning Tandberg on 10/05/2025.
//

#ifndef USB_RUBBER_DUCKY_KEYPRESSMAPPER_H
#define USB_RUBBER_DUCKY_KEYPRESSMAPPER_H

// Source and Inspiration
// https://stackoverflow.com/questions/58902217/fast-and-maintainable-way-of-implementing-string-to-integer-lookup-table
// https://stackoverflow.com/questions/114085/fast-string-hashing-algorithm-with-low-collision-rates-with-32-bit-integer
// https://medium.com/@ryan_forrester_/using-switch-statements-with-strings-in-c-a-complete-guide-efa12f64a59d

#include <string_view>
#include <iostream>

constexpr uint64_t hash(std::string_view str) {
    uint64_t hash = 0;
    for (char c : str) {
        hash = (hash * 131) + c;
    }
    return hash;
}

constexpr uint64_t operator"" _hash(const char* str, size_t len) {
    return hash(std::string_view(str, len));
}

std::uint8_t lookup_keypress(std::string_view action) {
    switch (hash(action)) {
        // Modifiers
        case "LEFT_CTRL"_hash:      return 0x80;
        case "LEFT_SHIFT"_hash:     return 0x81;
        case "LEFT_ALT"_hash:       return 0x82;
        case "LEFT_GUI"_hash:       return 0x83;
        case "RIGHT_CTRL"_hash:     return 0x84;
        case "RIGHT_SHIFT"_hash:    return 0x85;
        case "RIGHT_ALT"_hash:      return 0x86;
        case "RIGHT_GUI"_hash:      return 0x87;

        // Special
        case "BACKSPACE"_hash:      return 0xB2;
        case "TAB"_hash:            return 0xB3;
        case "RETURN"_hash:         return 0xB0;
        case "MENU"_hash:           return 0xED;
        case "CAPS_LOCK"_hash:      return 0xC1;

        // Navigation
        case "UP_ARROW"_hash:       return 0xDA;
        case "DOWN_ARROW"_hash:     return 0xD9;
        case "LEFT_ARROW"_hash:     return 0xD8;
        case "RIGHT_ARROW"_hash:    return 0xD7;
        case "ESC"_hash:            return 0xB1;
        case "INSERT"_hash:         return 0xD1;
        case "DELETE"_hash:         return 0xD4;
        case "PAGE_UP"_hash:        return 0xD3;
        case "PAGE_DOWN"_hash:      return 0xD6;
        case "HOME"_hash:           return 0xD2;
        case "END"_hash:            return 0xD5;

        // Numeric keypad
        case "NUM_LOCK"_hash:       return 0xDB;
        case "KP_SLASH"_hash:       return 0xDC;
        case "KP_ASTERISK"_hash:    return 0xDD;
        case "KP_MINUS"_hash:       return 0xDE;
        case "KP_PLUS"_hash:        return 0xDF;
        case "KP_ENTER"_hash:       return 0xE0;
        case "KP_1"_hash:           return 0xE1;
        case "KP_2"_hash:           return 0xE2;
        case "KP_3"_hash:           return 0xE3;
        case "KP_4"_hash:           return 0xE4;
        case "KP_5"_hash:           return 0xE5;
        case "KP_6"_hash:           return 0xE6;
        case "KP_7"_hash:           return 0xE7;
        case "KP_8"_hash:           return 0xE8;
        case "KP_9"_hash:           return 0xE9;
        case "KP_0"_hash:           return 0xEA;
        case "KP_DOT"_hash:         return 0xEB;

        // Escape and Function keys
        case "F1"_hash:             return 0xC2;
        case "F2"_hash:             return 0xC3;
        case "F3"_hash:             return 0xC4;
        case "F4"_hash:             return 0xC5;
        case "F5"_hash:             return 0xC6;
        case "F6"_hash:             return 0xC7;
        case "F7"_hash:             return 0xC8;
        case "F8"_hash:             return 0xC9;
        case "F9"_hash:             return 0xCA;
        case "F10"_hash:            return 0xCB;
        case "F11"_hash:            return 0xCC;
        case "F12"_hash:            return 0xCD;
        case "F13"_hash:            return 0xF0;
        case "F14"_hash:            return 0xF1;
        case "F15"_hash:            return 0xF2;
        case "F16"_hash:            return 0xF3;
        case "F17"_hash:            return 0xF4;
        case "F18"_hash:            return 0xF5;
        case "F19"_hash:            return 0xF6;
        case "F20"_hash:            return 0xF7;
        case "F21"_hash:            return 0xF8;
        case "F22"_hash:            return 0xF9;
        case "F23"_hash:            return 0xFA;
        case "F24"_hash:            return 0xFB;

        // Function Control Keys
        case "PRINT_SCREEN"_hash:   return 0xCE;
        case "SCROLL_LOCK"_hash:    return 0xCF;
        case "PAUSE"_hash:          return 0xD0;

        // Letter keys
        case "0"_hash:              return 0x30;
        case "1"_hash:              return 0x31;
        case "2"_hash:              return 0x32;
        case "3"_hash:              return 0x33;
        case "4"_hash:              return 0x34;
        case "5"_hash:              return 0x35;
        case "6"_hash:              return 0x36;
        case "7"_hash:              return 0x37;
        case "8"_hash:              return 0x38;
        case "9"_hash:              return 0x39;

        case "A"_hash:              return 0x41;
        case "B"_hash:              return 0x42;
        case "C"_hash:              return 0x43;
        case "D"_hash:              return 0x44;
        case "E"_hash:              return 0x45;
        case "F"_hash:              return 0x46;
        case "G"_hash:              return 0x47;
        case "H"_hash:              return 0x48;
        case "I"_hash:              return 0x49;
        case "J"_hash:              return 0x4A;
        case "K"_hash:              return 0x4B;
        case "L"_hash:              return 0x4C;
        case "M"_hash:              return 0x4D;
        case "N"_hash:              return 0x4E;
        case "O"_hash:              return 0x4F;
        case "P"_hash:              return 0x50;
        case "Q"_hash:              return 0x51;
        case "R"_hash:              return 0x52;
        case "S"_hash:              return 0x53;
        case "T"_hash:              return 0x54;
        case "U"_hash:              return 0x55;
        case "V"_hash:              return 0x56;
        case "W"_hash:              return 0x57;
        case "X"_hash:              return 0x58;
        case "Y"_hash:              return 0x59;
        case "Z"_hash:              return 0x5A;

        case "a"_hash:              return 0x61;
        case "b"_hash:              return 0x62;
        case "c"_hash:              return 0x63;
        case "d"_hash:              return 0x64;
        case "e"_hash:              return 0x65;
        case "f"_hash:              return 0x66;
        case "g"_hash:              return 0x67;
        case "h"_hash:              return 0x68;
        case "i"_hash:              return 0x69;
        case "j"_hash:              return 0x6A;
        case "k"_hash:              return 0x6B;
        case "l"_hash:              return 0x6C;
        case "m"_hash:              return 0x6D;
        case "n"_hash:              return 0x6E;
        case "o"_hash:              return 0x6F;
        case "p"_hash:              return 0x70;
        case "q"_hash:              return 0x71;
        case "r"_hash:              return 0x72;
        case "s"_hash:              return 0x73;
        case "t"_hash:              return 0x74;
        case "u"_hash:              return 0x75;
        case "v"_hash:              return 0x76;
        case "w"_hash:              return 0x77;
        case "x"_hash:              return 0x78;
        case "y"_hash:              return 0x79;
        case "z"_hash:              return 0x7A;

        default:                    return 0x00;
    }
}

#define KEY_BACKSPACE     0xB2
#define KEY_TAB           0xB3
#define KEY_RETURN        0xB0
#define KEY_MENU          0xED // "Keyboard Application" in USB standard
#define KEY_CAPS_LOCK     0xC1

// Misc keys
#define KEY_UP_ARROW      0xDA
#define KEY_DOWN_ARROW    0xD9
#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
#define KEY_ESC           0xB1
#define KEY_INSERT        0xD1
#define KEY_DELETE        0xD4
#define KEY_PAGE_UP       0xD3
#define KEY_PAGE_DOWN     0xD6
#define KEY_HOME          0xD2
#define KEY_END           0xD5

// Numeric keypad
#define KEY_NUM_LOCK      0xDB
#define KEY_KP_SLASH      0xDC
#define KEY_KP_ASTERISK   0xDD
#define KEY_KP_MINUS      0xDE
#define KEY_KP_PLUS       0xDF
#define KEY_KP_ENTER      0xE0
#define KEY_KP_1          0xE1
#define KEY_KP_2          0xE2
#define KEY_KP_3          0xE3
#define KEY_KP_4          0xE4
#define KEY_KP_5          0xE5
#define KEY_KP_6          0xE6
#define KEY_KP_7          0xE7
#define KEY_KP_8          0xE8
#define KEY_KP_9          0xE9
#define KEY_KP_0          0xEA
#define KEY_KP_DOT        0xEB

// Function keys
#define KEY_F1            0xC2
#define KEY_F2            0xC3
#define KEY_F3            0xC4
#define KEY_F4            0xC5
#define KEY_F5            0xC6
#define KEY_F6            0xC7
#define KEY_F7            0xC8
#define KEY_F8            0xC9
#define KEY_F9            0xCA
#define KEY_F10           0xCB
#define KEY_F11           0xCC
#define KEY_F12           0xCD
#define KEY_F13           0xF0
#define KEY_F14           0xF1
#define KEY_F15           0xF2
#define KEY_F16           0xF3
#define KEY_F17           0xF4
#define KEY_F18           0xF5
#define KEY_F19           0xF6
#define KEY_F20           0xF7
#define KEY_F21           0xF8
#define KEY_F22           0xF9
#define KEY_F23           0xFA
#define KEY_F24           0xFB

#define KEY_PRINT_SCREEN  0xCE // Print Screen / SysRq
#define KEY_SCROLL_LOCK   0xCF
#define KEY_PAUSE         0xD0 // Pause / Break

#endif //USB_RUBBER_DUCKY_KEYPRESSMAPPER_H
