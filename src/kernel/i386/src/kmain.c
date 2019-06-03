#include <stdint.h>
#include <tty.h>
#include <serial.h>
#include <stdio.h>
#include <string.h>

void kmain(struct multiboot *mboot_ptr) {
    ttyinit(0);
    serialinit(COM1,1);
    setprint(1);
    printf("Hello");
    char a = read_serial();
    printf("%c",a);
}
 
