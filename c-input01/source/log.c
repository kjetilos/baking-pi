#include "uart.h"
#include <types.h>

void LogPrint(char * message, u32 size)
{
	uart_puts(message);
	uart_puts("\r\n");
}