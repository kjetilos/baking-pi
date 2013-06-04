#include <stdint.h>

static uint32_t current_seed = 0;

/* Xn+1 = a*Xn^2 + b*x + c mod 2^32*/
uint32_t Random(uint32_t seed)
{
	// a = 0xef00
	// b = 1
	// c = 73
	return (0xef00 * seed * seed) + seed + 73;
}

uint32_t NextRandom(void)
{
	current_seed = Random(current_seed);
	return current_seed;
}