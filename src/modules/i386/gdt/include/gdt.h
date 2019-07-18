#pragma once

#include <stdint.h>

struct gdt_ptr_s {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct gdt_s {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t gran;
    uint8_t base_high;
};

typedef struct gdt_ptr_s gdt_ptr_t;
typedef struct gdt_s gdt_t;


// Initialize IDT and the GDT
void gdtinit();