#include <timer.h>

void timerstart(uint32_t freq, isr_t handler) {
    

    int divisor = 1193180 / freq;
    
    outb(0x43,0x36);

    outb(0x40,(uint8_t) divisor & 0xFF);
    outb(0x40,(uint8_t) (divisor >> 8) & 0xFF);
    register_interrupt_handler(IRQ0,handler);
}