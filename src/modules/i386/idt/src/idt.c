#include <idt.h>
#include <string.h>

// This is mostly from the James' kernel tutorial.

idt_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void flushidt(uint32_t);

void idtinit() {
    idt_ptr.limit = sizeof(idt_t) * 256 -1;
    idt_ptr.base  = (uint32_t) &idt_entries;

    memset(&idt_entries, 0, sizeof(idt_t)*256);
    
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    idtgate( 0, (uint32_t)isr0 , 0x08, 0x8E);
    idtgate( 1, (uint32_t)isr1 , 0x08, 0x8E);
    idtgate( 2, (uint32_t)isr2 , 0x08, 0x8E);
    idtgate( 3, (uint32_t)isr3 , 0x08, 0x8E);
    idtgate( 4, (uint32_t)isr4 , 0x08, 0x8E);
    idtgate( 5, (uint32_t)isr5 , 0x08, 0x8E);
    idtgate( 6, (uint32_t)isr6 , 0x08, 0x8E);
    idtgate( 7, (uint32_t)isr7 , 0x08, 0x8E);
    idtgate( 8, (uint32_t)isr8 , 0x08, 0x8E);
    idtgate( 9, (uint32_t)isr9 , 0x08, 0x8E);
    idtgate(10, (uint32_t)isr10, 0x08, 0x8E);
    idtgate(11, (uint32_t)isr11, 0x08, 0x8E);
    idtgate(12, (uint32_t)isr12, 0x08, 0x8E);
    idtgate(13, (uint32_t)isr13, 0x08, 0x8E);
    idtgate(14, (uint32_t)isr14, 0x08, 0x8E);
    idtgate(15, (uint32_t)isr15, 0x08, 0x8E);
    idtgate(16, (uint32_t)isr16, 0x08, 0x8E);
    idtgate(17, (uint32_t)isr17, 0x08, 0x8E);
    idtgate(18, (uint32_t)isr18, 0x08, 0x8E);
    idtgate(19, (uint32_t)isr19, 0x08, 0x8E);
    idtgate(20, (uint32_t)isr20, 0x08, 0x8E);
    idtgate(21, (uint32_t)isr21, 0x08, 0x8E);
    idtgate(22, (uint32_t)isr22, 0x08, 0x8E);
    idtgate(23, (uint32_t)isr23, 0x08, 0x8E);
    idtgate(24, (uint32_t)isr24, 0x08, 0x8E);
    idtgate(25, (uint32_t)isr25, 0x08, 0x8E);
    idtgate(26, (uint32_t)isr26, 0x08, 0x8E);
    idtgate(27, (uint32_t)isr27, 0x08, 0x8E);
    idtgate(28, (uint32_t)isr28, 0x08, 0x8E);
    idtgate(29, (uint32_t)isr29, 0x08, 0x8E);
    idtgate(30, (uint32_t)isr30, 0x08, 0x8E);
    idtgate(31, (uint32_t)isr31, 0x08, 0x8E);
    idtgate(32, (uint32_t)irq0 , 0x08, 0x8E); // These are for the IRQ's
    idtgate(33, (uint32_t)irq1 , 0x08, 0x8E);
    idtgate(34, (uint32_t)irq2 , 0x08, 0x8E);
    idtgate(35, (uint32_t)irq3 , 0x08, 0x8E);
    idtgate(36, (uint32_t)irq4 , 0x08, 0x8E);
    idtgate(37, (uint32_t)irq5 , 0x08, 0x8E);
    idtgate(38, (uint32_t)irq6 , 0x08, 0x8E);
    idtgate(39, (uint32_t)irq7 , 0x08, 0x8E);
    idtgate(40, (uint32_t)irq8 , 0x08, 0x8E);
    idtgate(41, (uint32_t)irq9 , 0x08, 0x8E);
    idtgate(42, (uint32_t)irq10, 0x08, 0x8E);
    idtgate(43, (uint32_t)irq11, 0x08, 0x8E);
    idtgate(44, (uint32_t)irq12, 0x08, 0x8E);
    idtgate(45, (uint32_t)irq13, 0x08, 0x8E);
    idtgate(46, (uint32_t)irq14, 0x08, 0x8E);
    idtgate(47, (uint32_t)irq15, 0x08, 0x8E);

    flushidt((uint32_t) &idt_ptr);
    
}

void idtgate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   idt_entries[num].flags   = flags ;
}