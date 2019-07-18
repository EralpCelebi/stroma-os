#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <tty.h>
#include <string.h>

#define WIDTH  80
#define HEIGHT 25
static uint16_t* const BUFFER = (uint16_t*) 0xB8000;

static size_t head_x;
static size_t head_y;

static uint8_t termcolor;
uint16_t tty1[WIDTH * HEIGHT];
uint16_t tty2[WIDTH * HEIGHT];
uint16_t tty3[WIDTH * HEIGHT];
static uint16_t* ttybuffer;
static uint8_t ttymode;


// ANCHOR VGA Update Function.

// NOTE May need some tinkering.

void ttyunload(uint8_t mode) {
    if (mode == 0) {
        // Do nothing if we are directly writing to the buffer.
    } else {
        uint16_t ttymode_old = ttymode;
        ttyset(mode);
        for (size_t index=0; index < WIDTH*HEIGHT; index++) {
            ttybuffer[index] = BUFFER[index];
        }
        ttyset(ttymode_old);
    }
}

void ttyload(uint8_t mode) {
    if (mode == 0) {
        // Do nothing if we are directly writing to the buffer.
    } else { 
        uint16_t ttymode_old = ttymode;
        ttyset(mode);
        for (size_t index=0; index < WIDTH*HEIGHT; index++) {
            BUFFER[index] = ttybuffer[index];
        }
        ttyset(ttymode_old);
    }
}

void ttyset(uint8_t mode) {
    switch (ttymode)
    {
    case 0:
        ttybuffer = BUFFER;
        ttymode = mode;
        break;
    case 1:
        ttybuffer = *tty1;
        ttymode = mode;
    case 2:
        ttybuffer = *tty2;
        ttymode = mode;    
    case 3:
        ttybuffer = *tty3;
        ttymode = mode;

    default:
        break;
    }
}

void ttyinit(uint8_t mode) {
    ttymode = mode;
    head_x = 0;
    head_y = HEIGHT - 1; // NOTE This is done just for the looks :p
    termcolor = colorpair(lightblue,black);
    ttyset(mode);
    ttyclear();
}

void ttychcolor(uint8_t c) {
    termcolor = c;
}

uint8_t ttygetcolor() {
    return termcolor;
}

void putbyte(unsigned char uc, uint8_t color, uint8_t x , uint8_t y) {
    size_t index = y * WIDTH + x;
    ttybuffer[index] = packedchar(uc, color);
}

void writechar(char uc) {
    if (head_x + 1 > WIDTH) {
        ttynline();
    }

    if (uc == '\n') {
        ttynline();
    } else {
        putbyte(uc,termcolor,head_x,head_y);
        head_x++;
    }
    
}

void writestr(char* str){
    for(int i=0;i < strlen(str); i++) {
        writechar(str[i]);
    }
}

void ttyscroll() {
    for (int index = 0; index <= WIDTH*(HEIGHT-1); index++) {
        ttybuffer[index] = ttybuffer[index + WIDTH];
    }

    for (int index = WIDTH*(HEIGHT-1); index <= WIDTH*HEIGHT; index++) {
        ttybuffer[index] = packedchar(' ', termcolor);
    }
}

void ttynline() {
    head_x = 0;
    if (head_y + 1 >= HEIGHT) {
        ttyscroll();
    } else { 
        head_y++;
    }
}

void ttyclear() {
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            size_t index = y * WIDTH + x;
            ttybuffer[index] = packedchar(' ', termcolor);
        }
    }
}