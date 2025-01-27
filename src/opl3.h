#ifndef OPL3_H
#define OPL3_H
#include <stdint.h>

#define OPL_BASE 0xC0600000

#define OPL_READ_REGS ((volatile struct opl3Read*) OPL_BASE)
#define OPL_WRITE_REGS ((volatile struct opl3Write*) OPL_BASE)


struct opl3Write{
    volatile uint8_t primInd;
    volatile uint8_t primData;
    volatile uint8_t secInd;
    volatile uint8_t secData;
};

struct opl3Read
{
    volatile uint8_t status;
};

void detectOpl(void);

#endif
