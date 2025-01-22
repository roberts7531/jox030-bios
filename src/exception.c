#include <stdint.h>
#include "exception.h"

struct StackFrame0* stackFrame;

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

void printStackFrame(struct StackFrame0* frame){
    char buffer[11];
    print("SR: ");
    uint32_to_hex(stackFrame->sr, buffer);
    print(buffer);
    print(" PC: ");
    uint32_to_hex(stackFrame->pc, buffer);
    print(buffer);
    print(" TYPE: ");
    uint32_to_hex(stackFrame->excType, buffer);
    print(buffer);
    print("\n");
}

void __attribute__((interrupt)) genericHandler(void){
    
    stackFrame = (struct StackFrame0*)((uint32_t*)__builtin_frame_address(0) + 1);
    print("\nException!\n");
    printStackFrame(stackFrame);
    print("\n");

}

void installHandler(int vector, uint32_t handler){
    uint32_t* vectorBase = (uint32_t*)0x0;
    vectorBase += vector;
    *vectorBase = handler;
}



void initializeGenericHandling(){
    uint32_t* vector = (uint32_t*)0x0;
    for(int i = 2; i<255;i++ ){
        *(vector+i) = (uint32_t) genericHandler;
    }
    __asm("move    #0x2000,%sr");
}