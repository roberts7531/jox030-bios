#include "util.h"
#include <stdint.h>

void uint_to_hex(uint32_t value, char *buffer, int fixed_size, bool include_prefix) {
    const char *hex_chars = "0123456789ABCDEF";
    int start = 0;

    if (include_prefix) {
        buffer[0] = '0';
        buffer[1] = 'x';
        start = 2;
    }

    if (fixed_size > 8) {
        fixed_size = 8;
    }

    for (int i = 0; i < fixed_size; i++) {
        int shift = (fixed_size - 1 - i) * 4; // Calculate shift for current nibble
        buffer[start++] = hex_chars[(value >> shift) & 0xF];
    }

    buffer[start] = '\0'; // Null-terminate the string
}

void printNumHex(uint32_t num, int fixed_size, bool include_prefix) {
    char buffer[11]; 
    uint_to_hex(num, buffer, fixed_size, include_prefix);
    print(buffer);
}


