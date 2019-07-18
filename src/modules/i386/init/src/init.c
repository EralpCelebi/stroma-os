#include <stdint.h>
#include <tty.h>
#include <serial.h>
#include <stdio.h>
#include <string.h>
#include <idt.h>
#include <gdt.h>
#include <init.h>

void state(unsigned char state) {
    uint8_t oldcolor = ttygetcolor();
    printf("[ ");
    if (state) {
        ttychcolor(colorpair(green,black));
        printf("OK");
        
    } else {
        ttychcolor(colorpair(red,black));
        printf("FAIL");
    }

    ttychcolor(oldcolor);
    printf(" ] ");
}

// TODO ACTUALLY ADD TESTS TO THIS
//  This code just depends on interrupts halting the system right now.

void init() {
    ttyinit(TTY0);
    state(1);
    printf("Screen Buffer Set. \n");
    gdtinit();
    state(1);
    printf("New GDT Loaded.\n"); // Check if you can switch 'ds' without causing a GPE
    idtinit();
    state(1);
    printf("New IDT Loaded.\n"); // I guess they will be checked whenever a software int. is thrown
    state(1);
    printf("Interrupt Handling Enabled.\n");
    asm volatile("sti");
    state(1);
    printf("Interrupt Handlers Set.\n"); // Right here. Check this using an interrupt. If the interrupt handler is actually functional it will return back.
    state(0);
    printf("Keyboard enabled.\n");
    state(0);
    printf("Timer enabled.\n");
    state(0);
    printf("Paging enabled.\n");
    serialinit(COM1,1);
    state(1);
    printf("Serial Comm. Initialized.\n"); // Really have no idea about how to check this.
    state(0);
    printf("Heap setup.\n");
    state(0);
    printf("VFS setup.\n");
    state(0);
    printf("Initrd loaded.\n");
    state(0);
    printf("Multitasking loaded.\n\n");
}