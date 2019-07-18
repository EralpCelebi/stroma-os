#include <stdio.h>
#include <string.h>
#include <tty.h>
 
void puts(const char* string) {
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == '\0') {
			break;
		} else {
			putchar(string[i]);
		}
	}
}