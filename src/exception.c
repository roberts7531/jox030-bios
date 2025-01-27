#include <stdint.h>
#include "exception.h"
#include "uart.h"
#include "gpu.h"
#include <stdbool.h>
#include "util.h"
#include "console.h"

struct StackFrame0* stackFrame;


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
    setMode(GPU_MODE_TEXT);
    stackFrame = (struct StackFrame0*)((uint32_t*)__builtin_frame_address(0) + 1);
    print(vectorNames[stackFrame->excType&EXCTYPE_MASK_VECTOR]);
    print(" Exception!\n");
    printStackFrame(stackFrame);
    print("\n");
    while(1);
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
