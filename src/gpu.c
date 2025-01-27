#include <stdint.h>
#include "gpu.h"

void gpuWriteReg(uint8_t reg, uint8_t data){
	*((volatile uint8_t*)GPU_IO_WPROT) = 0xaf;
	*((volatile uint8_t*)GPU_IO_REGNO) = reg;
	*((volatile uint8_t*)GPU_IO_DATA) = data;
}

void setColor(uint8_t index, struct Color* color){
    gpuWriteReg(GPU_REG_CINDEX,index);
    gpuWriteReg(GPU_REG_CRED,color->red);
    gpuWriteReg(GPU_REG_CGREEN,color->green);
    gpuWriteReg(GPU_REG_CBLUE,color->blue);
}
void setMode(uint8_t mode){
    gpuWriteReg(GPU_REG_MODE,mode);
}

void initGPU(){
    setMode(GPU_MODE_TEXT);
    volatile uint8_t* vram = (uint8_t*)GPU_VRAM_BASE;
    for(uint32_t i = 0;i<65536;i++){
        *(vram+i) = 0;
    }
}