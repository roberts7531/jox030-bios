    .section .startup
    .long _stack_top
    .long _start


    .global main


_start:
    lea _stack_top, %a7
    lea _vram_start, %a0
    move.b #'A',(%a0)
    move    #0x2700,%sr
    lea _data_load, %a0
    lea _data_start, %a1
    lea _data_end, %a2

copy_data:
    move.b #'B',(_vram_start)
    cmpa.l %a2, %a1
    beq clear_bss
    move.b (%a0)+, (%a1)+
    bra copy_data

clear_bss:
    lea _bss_start, %a1
    lea _bss_end, %a2
zero_bss:
    move.b #'C',(_vram_start)
    cmpa.l %a2, %a1
    beq init_done
    clr.b (%a1)+
    bra zero_bss

init_done:
    movea.l #_vram_start,%a0
    move.b #'D',(%a0)
    jmp main
    jmp init_done