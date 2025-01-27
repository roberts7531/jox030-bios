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

void hexDump(void *addr, uint32_t length) {
    uint8_t *data = (uint8_t *)addr;
    print("Starting hexdump at: ");
    printNumHex((uint32_t)data, 8, true);
    print("\n");

    for (size_t i = 0; i < length; i += 16) {
        printNumHex(i,8, true);
        print(": ");

        for (size_t j = 0; j < 16 && i + j < length; ++j) {
            printNumHex(data[i + j], 2, false);
            print(" ");
        }

        print("  ");
        for (size_t j = 0; j < 16 && i + j < length; ++j) {
            unsigned char c = data[i + j];
            print((c >= 32 && c <= 126) ? (char[]){(char)c, '\0'} : (char[]){'.', '\0'});
        }

        print("\n");
    }
}


