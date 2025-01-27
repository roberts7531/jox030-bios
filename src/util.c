#include "util.h"
#include <stdint.h>

void uint32_to_hex(uint32_t value, char *buffer) {
    const char *hex_chars = "0123456789ABCDEF";
    buffer[0] = '0'; // Prefix
    buffer[1] = 'x';
    for (int i = 0; i < 8; i++) {
        buffer[9 - i] = hex_chars[value & 0xF]; // Get last 4 bits
        value >>= 4;                           // Shift right by 4 bits
    }
    buffer[10] = '\0'; // Null-terminate the string
}

void printNumHex(uint32_t num){
    char buffer[11];
    uint32_to_hex(num, buffer);
    print(buffer);
}
