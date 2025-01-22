#ifndef EXCEPTION_H
#define EXCEPTION_H
struct StackFrame0{
    uint16_t sr;
    uint32_t pc;
    uint16_t excType;
} __attribute__ ((packed));
void initializeGenericHandling(void);
void __attribute__((interrupt)) genericHandler(void);
void installHandler(int vector, uint32_t handler);
#endif