#include <stdio.h>
#include <stdint.h>

int main(void)
{
	for (int i=0; i<10; i++) {
	    uint32_t x0 = NextRandom(400);
	    uint32_t y0 = NextRandom(400);
    	uint32_t x1 = NextRandom(400);
    	uint32_t y1 = NextRandom(400);

		printf("(%u, %u) - (%u, %u)\n", x0, y0, x1, y1);
	}

	char buffer[12];
	int_to_char(468, buffer);
	int_to_char(~0, buffer);
	printf("%s\n", buffer);
	return 0;
}