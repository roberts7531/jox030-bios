#include "uart.h"
#include <stdbool.h>
#include "exception.h"

volatile bool uartPresent = false;
volatile int dummy;

void __attribute__((interrupt)) detectUartHandler(void){
    dummy = UART_READ_REGS->stopCounter;
    dummy = UART_READ_REGS->ISR;
    UART_WRITE_REGS -> IMR = 0;
    print("Uart detected!/n");
    uartPresent = true;
    installHandler(30,(uint32_t)genericHandler);
}

void detectUart(){
    //installHandler();
    print("Trying uart");
    UART_WRITE_REGS->IMR = 0x08;
    UART_WRITE_REGS->ACR = 0xFF;
    UART_WRITE_REGS->CTUR = 0xFF;
    UART_WRITE_REGS->CTLR = 0xff; 
    installHandler(30,(uint32_t)detectUartHandler);
    dummy = UART_READ_REGS->startCounter;
}






void ioTest(){
    UART_WRITE_REGS->OPCR = 0;
    UART_WRITE_REGS->setOutput = 0x55;
}