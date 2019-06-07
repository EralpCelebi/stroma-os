#include <gdt.h>
#include <string.h>

// This part is mostly taken from JamesM's kernel tutorial.

gdt_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

extern void flushgdt(uint32_t);

void gdtinit() {
   gdt_ptr.limit = (sizeof(gdt_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t) &gdt_entries;

   gdtgate(0, 0, 0, 0, 0);                // Null segment
   gdtgate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdtgate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdtgate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdtgate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   flushgdt((uint32_t) &gdt_ptr);
}

// Set the value of one GDT entry.
void gdtgate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gr) {
   gdt_entries[num].base_low = (base & 0xFFFF);
   gdt_entries[num].base_mid = (base >> 16) & 0xFF;
   gdt_entries[num].base_high = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low = (limit & 0xFFFF);
   gdt_entries[num].gran = (limit >> 16) & 0x0F;

   gdt_entries[num].gran |= gr & 0xF0;
   gdt_entries[num].access = access;
}