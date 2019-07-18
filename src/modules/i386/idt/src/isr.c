#include <stdio.h>
#include <isr.h>
#include <tty.h>
#include <io.h>

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void irq_handler(registers_t* regs) {
   if (regs->int_no >= 40)
   {
       outb(0xA0, 0x20);
   }
   outb(0x20, 0x20);

   if (interrupt_handlers[regs->int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs->int_no];
       handler(regs);
   }
}

isr_t* interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t* handler)
{
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t* regs) {
    char *exception_messages[] = {
      "Division By Zero",
      "Debug",
      "Non Maskable Interrupt",
      "Breakpoint",
      "Into Detected Overflow",
      "Out of Bounds",
      "Invalid Opcode",
      "No Coprocessor",

      "Double Fault",
      "Coprocessor Segment Overrun",
      "Bad TSS",
      "Segment Not Present",
      "Stack Fault",
      "General Protection Fault",
      "Page Fault",
      "Unknown Interrupt",

      "Coprocessor Fault",
      "Alignment Check",
      "Machine Check",
      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved",

      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved",
      "Reserved"
   };
    
    if (interrupt_handlers[regs->int_no]) {
      isr_t* handler = interrupt_handlers[regs->int_no];
      (*handler)(regs);
    } else {
      printf("Unhandled interrupt: %s (%x) with err. code: %x \n", exception_messages[regs->int_no],regs->int_no, regs->err_code);
    }
}

void irq_handler(registers_t* regs)
{
    if (regs->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }
    
    outb(0x20, 0x20);
    
    if (interrupt_handlers[regs->int_no])
    {
      isr_t* handler = interrupt_handlers[regs->int_no];
      (*handler)(regs);
    } else {
      printf("Unhandled interrupt: (%x) with err. code: %x \n",regs->int_no, regs->err_code);
    }

}


