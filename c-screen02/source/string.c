#include <stdint.h>

static char table[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9'
};

void int_to_char(uint32_t number, char * buffer)
{
	int index = 0;
	uint32_t tmp = number;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		buffer[index] = 0;
		index++;
	}
	index--;

	while (number > 0)
	{
		uint32_t digit = number % 10;
		number = number / 10;
		buffer[index] = table[digit];
		index--;
	}
}