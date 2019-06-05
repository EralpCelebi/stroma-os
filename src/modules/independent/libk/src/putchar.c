#include <stdio.h>
#include <tty.h>
#include <serial.h>

// TODO IMPLEMENT SYSCALL-

static uint8_t target = 0;

void setprint(uint8_t targ) {
	target = targ;
}

void putchar(char c) {
	if (target == 0) {
		writechar(c);
	} else {
		write_serial(c);
	}
}