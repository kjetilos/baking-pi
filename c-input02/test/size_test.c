#include "designware20.h"
#include <stdio.h>
#include <stdint.h>


int main(void)
{
	printf("HostGlobalRegs: %#x (0x400), CoreGlobalRegs: %#x (0x400), PowerReg: %#x (0x4).\n", 
			sizeof(struct HostGlobalRegs), sizeof(struct CoreGlobalRegs), sizeof(struct PowerReg));
	return 0;
}