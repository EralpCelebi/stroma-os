
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)

bits 32
_start:
    mov esp, stack_top
    
    push ebx

    cli
    extern kmain
    call kmain

.hang:
    cli
    hlt
    jmp .hang
.end: