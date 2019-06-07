#include <stdint.h>
#include <tty.h>
#include <serial.h>
#include <stdio.h>
#include <string.h>
#include <idt.h>
#include <gdt.h>

void kmain(struct multiboot *mboot_ptr) {
    gdtinit();
    idtinit();
    ttyinit(TTY0);
    serialinit(COM1,1);
    asm volatile ("int $0x5");
    printf("Wow");
}
 
