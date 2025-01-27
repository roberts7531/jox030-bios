#include <stdint.h>
#include "exception.h"
#include "uart.h"
#include "gpu.h"
#include <stdbool.h>
#include "util.h"

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

volatile bool isRed  = false;
volatile int dummy2;
void __attribute__((interrupt)) screenFlashHandler(void){
    
    dummy2 = UART_READ_REGS->stopCounter;
    dummy2 = UART_READ_REGS->ISR;
    struct Color color;
    color.green = 0;
    color.blue = 0;
    if(isRed){
        color.red = 0;
        setColor(0,&color);
        isRed =false;
    }else{
        color.red = 0xff;
        setColor(0,&color);
        isRed = true;
    }

}

void __attribute__((interrupt)) genericHandler(void){
    
    stackFrame = (struct StackFrame0*)((uint32_t*)__builtin_frame_address(0) + 1);
    print("\nException!\n");
    setMode(GPU_MODE_COLOR);
    volatile uint8_t* vram = (uint8_t*)GPU_VRAM_BASE;
    for(uint32_t i = 0;i<65536;i++){
        *(vram+i) = 0;
    }
    struct Color color;
    color.red = 0xff;
    color.green = 0;
    color.blue = 0;
    setColor(0,&color);
    installHandler(30,screenFlashHandler);
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