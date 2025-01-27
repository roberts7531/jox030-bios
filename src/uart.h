#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_BASE 0xC0000000

#define UART_READ_REGS ((volatile struct uartRegsRead*) UART_BASE)
#define UART_WRITE_REGS ((volatile struct uartRegsWrite*) UART_BASE)
#define GPIO_MOSI 1
#define GPIO_SCK 2
#define GPIO_MISO 0

struct uartRegsRead{
    volatile uint8_t MRA;
    volatile uint8_t SRA;
    volatile uint8_t brgTest;
    volatile uint8_t RHRA;
    volatile uint8_t IPCR;
    volatile uint8_t ISR;
    volatile uint8_t CTU;
    volatile uint8_t CTL;
    volatile uint8_t MRB;
    volatile uint8_t SRB;
    volatile uint8_t test1x16x;
    volatile uint8_t RHRB;
    volatile uint8_t IVR;
    volatile uint8_t IP;
    volatile uint8_t startCounter;
    volatile uint8_t stopCounter;
};

struct uartRegsWrite{
    volatile uint8_t MRA;
    volatile uint8_t CSRA;
    volatile uint8_t CRA;
    volatile uint8_t THRA;
    volatile uint8_t ACR;
    volatile uint8_t IMR;
    volatile uint8_t CTUR;
    volatile uint8_t CTLR;
    volatile uint8_t MRB;
    volatile uint8_t CSRB;
    volatile uint8_t CRB;
    volatile uint8_t THRB;
    volatile uint8_t IVR;
    volatile uint8_t OPCR;
    volatile uint8_t setOutput;
    volatile uint8_t resetOutput;
};
void ioTest(void);
uint8_t spiExchange(uint8_t csPin, uint8_t dataOut);
void setOutput(uint8_t pin);
void resetOutPut(uint8_t pin);
#endif