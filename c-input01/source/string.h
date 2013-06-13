#ifndef STRING_H
#define STRING_H

#include <stdint.h>

uint32_t uint_to_char(uint32_t number, char * buffer, uint32_t base);
uint32_t int_to_char(int32_t number, char * buffer, uint32_t base);
uint32_t displayf(char * format, char * dest, ...);

#endif
