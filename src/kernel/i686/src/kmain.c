#include <stdint.h>
#include <tty.h>
#include <stdio.h>
#include <string.h>
#include <serial.h>

void kmain(struct multiboot *mboot_ptr) {
    ttyinit(0);
    printf("Can is %s", "Well");
    configure_com1_base();
    serial_is_transmit_fifo_empty(SERIAL_COM1_BASE);
}
