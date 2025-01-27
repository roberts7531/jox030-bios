#include <stdint.h>
#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 50
#define FRAMEBUFFER   ((volatile unsigned char*) 0xc0800000) // Replace with your framebuffer base address

// Cursor position
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

// Function to move the cursor to the start of the next line
void newline() {
    cursor_x = 0;
    cursor_y++;
    if (cursor_y >= SCREEN_HEIGHT) {
        cursor_y = SCREEN_HEIGHT - 1; // Scroll screen if at the bottom
        // You could implement scrolling by shifting framebuffer content up
    }
}

// Function to print a character to the framebuffer
void print_char(char c) {
    if (c == '\n') {
        newline();
        return;
    }

    // Write the character to the framebuffer at the current cursor position
    FRAMEBUFFER[cursor_y * SCREEN_WIDTH + cursor_x] = c;

    // Move the cursor to the next position
    cursor_x++;
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= SCREEN_HEIGHT) {
            cursor_y = SCREEN_HEIGHT - 1; // Scroll screen if at the bottom
        }
    }
}

// Function to print a string
void print(const char* str) {
    while (*str) {
        print_char(*str);
        str++;
    }
}
