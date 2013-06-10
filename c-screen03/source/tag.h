#ifndef TAG_H
#define TAG_H
 
#include <stdint.h>
 
struct tag {
	uint32_t tag_size;
	uint32_t tag_number;
	void * data;
};

void atag_init(uint32_t atags_addr);
struct tag atag_get(uint32_t tag);

#endif
