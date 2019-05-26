#include <stdint.h>
#include <tty.h>

void kmain(struct multiboot *mboot_ptr) {
    ttyinit(2);
    for (int i = 0; i < 80; i++) {
        writechar('-');
    }
    uint8_t col = colorpair(cyan, black);
    ttychcolor(col);
    writestr("AHOY!");
    ttyload(2);
    ttyset(0);
}