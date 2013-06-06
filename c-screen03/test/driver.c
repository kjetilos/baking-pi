#include <stdio.h>
#include <stdint.h>

extern uint8_t font_begin[];

int main(void)
{
	printf("Font symbol 0x%x &0x%x\n", font_begin, &font_begin);
	return 0;
}