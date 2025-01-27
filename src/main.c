#include <stdint.h>
#include "exception.h"
#include "uart.h"
#include "opl3.h"
#include "gpu.h"
#include "enc28j60.h"
#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 50
#define FRAMEBUFFER   ((volatile unsigned char*) 0xc0800000) // Replace with your framebuffer base address

// Cursor position
unsigned char cursor_x = 0;
unsigned char cursor_y = 0;

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

volatile uint64_t counter;
void delayLoop(){
    counter = 300000;
    while(counter>0){
        counter--;
    }
}


// Example usage
void main() {
    delayLoop();
    initGPU();
    print("Hello, World!\n");
    print("This is a test of the print routine.\n");
    print("Another line here!\n");
    initializeGenericHandling();
    detectUart();
    detectOpl();
    enableLed();
    initialize();
    while (1); // Infinite loop to halt execution
}
