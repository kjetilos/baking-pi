#include "tag.h"
#include <mmio.h>

static uint32_t atags_base = 0;

void atag_init(uint32_t atags_addr)
{
	atags_base = atags_addr;
}

struct tag atag_get(uint32_t id)
{
	struct tag tag = {0};
	uint32_t tag_addr = atags_base;
	uint32_t tag_size;
	uint32_t tag_number;
	do {
		tag_size = mmio_read(tag_addr);
		tag_number = mmio_read(tag_addr + 4);

		if (tag_number == id) 
		{
			tag.size = tag_size;
			tag.number = tag_number;
			tag.data = (void *)(tag_addr + 8);
			return tag;
		}
		tag_addr = tag_addr + (tag_size * 4);
	} while (tag_number != 0);

	return tag;
}