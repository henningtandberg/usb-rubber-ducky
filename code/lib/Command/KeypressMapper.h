//
// Created by Henning Tandberg on 10/05/2025.
//

#ifndef USB_RUBBER_DUCKY_KEYPRESSMAPPER_H
#define USB_RUBBER_DUCKY_KEYPRESSMAPPER_H

// Source and Inspiration
// https://stackoverflow.com/questions/58902217/fast-and-maintainable-way-of-implementing-string-to-integer-lookup-table
// https://stackoverflow.com/questions/114085/fast-string-hashing-algorithm-with-low-collision-rates-with-32-bit-integer
// https://medium.com/@ryan_forrester_/using-switch-statements-with-strings-in-c-a-complete-guide-efa12f64a59d

#include <string.h>
#include <stdint.h>

constexpr uint64_t hash(const char * str, size_t str_len) {
    uint64_t hash = 0;

    for (size_t i = 0; i < str_len; i++) {
        char c = str[i];
        hash = (hash * 131) + c;
    }

    return hash;
}

constexpr uint64_t operator"" _hash(const char* str, size_t len) {
    return hash(str, len);
}

uint8_t lookup_keypress(const char * str, size_t len);

#endif //USB_RUBBER_DUCKY_KEYPRESSMAPPER_H