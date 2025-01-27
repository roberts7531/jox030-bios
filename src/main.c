#include <stdint.h>
#include "exception.h"
#include "uart.h"
#include "opl3.h"
#include "gpu.h"
#include "enc28j60.h"

volatile uint64_t counter;
void delayLoop(){
    counter = 150000;
    while(counter>0){
        counter--;
    }
}


// Example usage
void main() {
    initGPU(); // clearing vram before delay in case of reset, looks kinda trash otherwise
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
