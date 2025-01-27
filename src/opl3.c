#include "opl3.h"
#include <stdbool.h>
#include "exception.h"
    volatile uint8_t status;
    volatile bool oplPresent = false;
void delay(){
    status = OPL_READ_REGS->status;
    status = OPL_READ_REGS->status;
    status = OPL_READ_REGS->status;
}

void __attribute__((interrupt)) detectOPLHandler(void){
    OPL_WRITE_REGS->primInd = 0x4;
    delay();
    OPL_WRITE_REGS->primData = 0x40;
    delay();
    OPL_WRITE_REGS->primInd = 0x4;
    delay();
    OPL_WRITE_REGS->primData = 0x80;
    delay();
    print("OPL3 detected!\n");
    oplPresent = true;
    installHandler(29,(uint32_t)genericHandler);
}
void detectOpl(){
    print("poking opl3\n");
    installHandler(29,(uint32_t)detectOPLHandler);

    OPL_WRITE_REGS->primInd = 0x04;
    delay();
    OPL_WRITE_REGS->primData = 0x60;
    delay();
    OPL_WRITE_REGS->primInd = 0x04;
    delay();
    OPL_WRITE_REGS->primData = 0x80;
    delay();
    OPL_WRITE_REGS->primInd = 0x02;
    delay();
    OPL_WRITE_REGS->primData = 0xff;
    delay();
    OPL_WRITE_REGS->primInd = 0x04;
    delay();
    OPL_WRITE_REGS->primData = 0x21;
    delay();
   
} 

