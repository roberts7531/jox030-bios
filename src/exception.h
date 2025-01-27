#ifndef EXCEPTION_H
#define EXCEPTION_H

struct StackFrame0{
    uint16_t sr;
    uint32_t pc;
    uint16_t excType;
} __attribute__ ((packed));

const char* vectorNames[] = {
    "Reset SP",
    "Reset PC",
    "Bus error",
    "Address error",
    "Illegal instruction",
    "Divide by zero",
    "CHK, CHK2 Instruction",
    "TRAPcc, TRAPV",
    "Privilege violation",
    "Trace",
    "Line A emulator",
    "Line F emulator",
    "Reserved",
    "Copro proto violation",
    "Format error",
    "Uninit interrupt",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Spurious interrupt",
    "LV1 Interrupt",
    "LV2 Interrupt",
    "LV3 Interrupt",
    "LV4 Interrupt",
    "LV5 Interrupt",
    "LV6 Interrupt",
    "LV7 Interrupt",
    "Trap 0",
    "Trap 1",
    "Trap 2",
    "Trap 3",
    "Trap 4",
    "Trap 5",
    "Trap 6",
    "Trap 7",
    "Trap 8",
    "Trap 9",
    "Trap 10",
    "Trap 11",
    "Trap 12",
    "Trap 13",
    "Trap 14",
    "Trap 15",
    "FPU Branch or set unordered",
    "FPU Inexact result",
    "FPU Divide by zero",
    "FPU Underflow",
    "FPU Operand error",
    "FPU Overflow",
    "FPU Signalling NaN",
    "Reserved",
    "MMU config error"
}


void initializeGenericHandling(void);
void __attribute__((interrupt)) genericHandler(void);
void installHandler(int vector, uint32_t handler);
#endif
