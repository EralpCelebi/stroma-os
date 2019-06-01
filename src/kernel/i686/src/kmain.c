#include <stdint.h>
#include <tty.h>
#include <stdio.h>
#include <string.h>

void kmain(struct multiboot *mboot_ptr) {
    ttyinit(0);
    printf("Heyoddfhgfd %s", "Hey");
}
 