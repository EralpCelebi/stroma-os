#include <string.h>

#include <stdint.h>
#include <stddef.h>

void memset(uint8_t *dest, uint8_t val, size_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
