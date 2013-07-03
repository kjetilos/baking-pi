#pragma once 
#include <stdint.h>
 
struct tag {
	uint32_t size;
	uint32_t number;
	void * data;
};

void atag_init(uint32_t atags_addr);
struct tag atag_get(uint32_t tag);
