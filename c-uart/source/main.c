#include <uart.h>

const char hello[] = "\r\nHello World\r\n";

void main()
{
  int i;

  uart_init();

  while (1) 
  {
    uart_puts(hello);
    for (i=0; i<0x3f0000; i++);
  }
}
