#ifndef GPU_H
#define GPU_H
#include <stdint.h>

#define GPU_IO_DATA 0xc080ffff
#define GPU_IO_REGNO 0xc080fffe
#define GPU_IO_WPROT 0xc080fffd
#define GPU_VRAM_BASE 0xC0800000

#define GPU_REG_MODE 0
#define GPU_REG_BLITSTART 1
#define GPU_REG_WIDTHLOW 2
#define GPU_REG_WIDTHHIGH 3
#define GPU_REG_HEIGHTLOW 4
#define GPU_REG_HEIGHTHIGH 5
#define GPU_REG_DYLOW 6
#define GPU_REG_DYHIGH 7
#define GPU_REG_DXLOW 8
#define GPU_REG_DXHIGH 9
#define GPU_REG_SYLOW 10
#define GPU_REG_SYHIGH 11
#define GPU_REG_SXLOW 12
#define GPU_REG_SXHIGH 13
#define GPU_REG_WRPROT 14
#define GPU_REG_CINDEX 15
#define GPU_REG_CRED 16
#define GPU_REG_CBLUE 17
#define GPU_REG_CGREEN 18

#define GPU_MODE_TEXT 0
#define GPU_MODE_COLOR 1
#define GPU_MODE_HIGHRES 2

struct Color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void initGPU(void);
void setColor(uint8_t index, struct Color* color);
void setMode(uint8_t mode);
#endif