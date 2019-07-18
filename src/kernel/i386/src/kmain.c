#include <stdint.h>
#include <tty.h>
#include <serial.h>
#include <stdio.h>
#include <string.h>
#include <idt.h>
#include <isr.h>
#include <gdt.h>
#include <timer.h>
#include <init.h>

int timer = 1;

void hey(registers_t* regs) {
    printf("%d\n",timer++);
}

void kmain(struct multiboot *mboot_ptr) {
    init();
    timerstart(20,&hey);
    for(;;);
}
 
