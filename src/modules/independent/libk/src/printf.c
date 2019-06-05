#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

char* convert(unsigned int num, int base) 
{
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}

void printf(const char* __restrict__ format,...) 
{ 
    char *traverse; 
    unsigned int i; 
    char *s; 

    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        if (*traverse == '\0') {
            break;
        }

        while( *traverse != '%' && *traverse != '\0') 
        { 
            putchar(*traverse);
            traverse++; 
        }

        if (*traverse == '\0') {
            break;
        } else {
            traverse++;
        }

        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     
                        putchar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);
                        if(i<0) 
                        { 
                            i = -i;
                            putchar('-'); 
                        } 
                        puts(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int);
                        puts(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);
                        puts(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int);
                        puts("0x");
                        puts(convert(i,16));
                        break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
}


