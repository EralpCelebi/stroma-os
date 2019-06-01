#pragma once

#include <stddef.h>
#include <stdint.h>

int memcmp(const void* aptr, const void* bptr, size_t size);
void memcpy(uint8_t *dest, const uint8_t *src, size_t len);
void memmove(void* dstptr, const void* srcptr, size_t size);
void memset(uint8_t* dest, uint8_t val, size_t len);
size_t strlen(const char*);