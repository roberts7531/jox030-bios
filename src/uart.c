#include "uart.h"
#include <stdbool.h>
#include "exception.h"

volatile bool uartPresent = false;
volatile bool ledState = false;
volatile int dummy;

void __attribute__((interrupt)) systemTickHandler(void){
    dummy = UART_READ_REGS->stopCounter;
    dummy = UART_READ_REGS->ISR;
    if(ledState){
        ledState =false;
    }else{
        ledState = true;
    }
}

void __attribute__((interrupt)) detectUartHandler(void){
    dummy = UART_READ_REGS->stopCounter;
    dummy = UART_READ_REGS->ISR;
    print("Uart detected!\n");
    uartPresent = true;
    installHandler(30,(uint32_t)systemTickHandler);
}


void detectUart(){
    //installHandler();
    print("Trying uart\n");
    installHandler(30,(uint32_t)detectUartHandler);
    UART_WRITE_REGS->ACR = 0xFF;
    UART_WRITE_REGS->CTUR = 0xFF;
    UART_WRITE_REGS->CTLR = 0xff; 
    UART_WRITE_REGS->IMR = 0x08;
    UART_WRITE_REGS->OPCR = 0;
    UART_WRITE_REGS->setOutput = 0xff;

    dummy = UART_READ_REGS->startCounter;
}


void setOutput(uint8_t pin)
{
    UART_WRITE_REGS->resetOutput = (1<<pin);
}
void resetOutPut(uint8_t pin){
    UART_WRITE_REGS->setOutput = (1<<pin);
}
bool readInput(uint8_t pin){
    return UART_READ_REGS->IP & (1<<pin);
}

uint8_t spiExchange(uint8_t csPin, uint8_t dataOut) {
    uint8_t dataIn = 0; // Initialize dataIn to store the received byte

    for (int i = 7; i >= 0; i--) {
        // Set the MOSI line to the appropriate bit of dataOut
        if (dataOut & (1 << i)) {
            setOutput(GPIO_MOSI);
        } else {
            resetOutPut(GPIO_MOSI);
        }

        // Pulse the clock line (SCK) high
        setOutput(GPIO_SCK);

        // Read the MISO line and shift it into dataIn
        if (readInput(GPIO_MISO)) {
            dataIn |= (1 << i);
        }

        // Pulse the clock line (SCK) low
        resetOutPut(GPIO_SCK);
    }

    // Set CS high to deselect the SPI device
    return dataIn;
}



void ioTest(){
    UART_WRITE_REGS->setOutput = 0x55;
}