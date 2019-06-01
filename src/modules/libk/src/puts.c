#include <stdio.h>
#include <tty.h>
 
void puts(const char* string) {
	writestr(string);
}