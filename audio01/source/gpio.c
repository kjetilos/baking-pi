#include "gpio.h"

static volatile unsigned * gpio = (void*) 0x20200000;

void gpio_function_select(unsigned pin, enum gpio_function function)
{
  if (pin > 54 || function > 7)
    return;

  int select_register = pin / 10;
  int function_select = (pin % 10) * 3;
  
  gpio[select_register] = function << function_select;
}

void gpio_set(unsigned pin, unsigned val)
{
  if (pin > 54)
    return;

  int set = pin / 32;
  int bit = 1 << (pin & 0x1f);

  if (val)
  {
    gpio[7+set] = bit;
  }
  else
  {
    gpio[10+set] = bit;
  }
}
