global flushgdt

flushgdt:
   mov eax, [esp+4]  
   lgdt [eax]

   mov ax, 0x10 ; Move everything
   mov ds, ax     
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush ; Jump with the offset of the kernel code segment
.flush:
   ret