#include <stdio.h>
#include <stdint.h>


int main(void)
{
	char buffer[20];
	uint32_t res = int_to_char(45, buffer, 10);
	printf("to_char = %s\n", buffer);
	res = int_to_char(-15, buffer, 10);
	printf("to_char = %s\n", buffer);
	res = int_to_char(255, buffer, 2);
	printf("int_to_char = %s\n", buffer);

	displayf("hello\n", buffer);
	printf(buffer);
	displayf("yo%%\n", buffer);
	printf(buffer);
	displayf("char=%c\n", buffer, 'r');
	printf(buffer);
	displayf("tall=%iEnd\n", buffer, 1234);
	printf(buffer);
	displayf("bin=0b%b\n", buffer, 254);
	printf(buffer);
	displayf("hex=0x%x\n", buffer, 254);
	printf(buffer);

	return 0;
}