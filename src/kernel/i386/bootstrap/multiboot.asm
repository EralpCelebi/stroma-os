; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            
MEMINFO  equ  1 << 1            
;VIDINFO  equ  1 << 2
FLAGS    equ  MBALIGN | MEMINFO 
MAGIC    equ  0x1BADB002        
CHECKSUM equ -(MAGIC + FLAGS)   
 

section .multiboot
header_start:
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
header_end: