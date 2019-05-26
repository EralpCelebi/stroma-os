#pragma once

#include <stdint.h>

enum color {
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,
	red = 4,
	magenta = 5,
	brown = 6,
	lightgrey = 7,
	darkgrey = 8,
	lightblue = 9,
	lightgreen = 10,
	lightcyan = 11,
	lightred = 12,
	lightmagenta = 13,
	lightbrown = 14,
	white = 15,
};
 
static inline uint8_t colorpair(enum color fg, enum color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t packedchar(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void ttyunload(uint8_t mode);
void ttyload(uint8_t mode);
void ttyset(uint8_t mode);
void ttyinit(uint8_t mode);
void ttychcolor(uint8_t c);
void putbyte(unsigned char uc, uint8_t color, uint8_t x , uint8_t y);
void writechar(char uc);
void writestr(char* str);
void ttyscroll();
void ttynline();
void ttyclear();