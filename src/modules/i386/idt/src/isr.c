#include <stdio.h>
#include <isr.h>
#include <tty.h>

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
    printf("Unhandled interrupt: %s (%x) with err. code: %x \n", exception_messages[regs->int_no],regs->int_no, regs->err_code);
}

