MEMORY
{
	ROM (rx)	: ORIGIN = 0x80000000, LENGTH = 512K
	RAM (rwx)	: ORIGIN = 0x00001000, LENGTH = 128K
    VRAM (rw)   : ORIGIN = 0xC0800000, LENGTH = 64K
}

SECTIONS
{
    . = 0x80000000;
	.text : ALIGN(4) {
		*(.startup)
		*(.text*)
		*(.rodata)
	} > ROM

	.data : ALIGN(4) {
        _data_load = LOADADDR(.data);
        _data_start = .;
		*(.data*)
        _data_end = .;
	} > RAM AT > ROM

	.bss : ALIGN(4) {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        _bss_end = .;
    } > RAM
    _vram_start = ORIGIN(VRAM);
    _stack_top = ORIGIN(RAM) + 256K; 
    _stack_bottom = _stack_top - 4K;           

    _end = .;
}
