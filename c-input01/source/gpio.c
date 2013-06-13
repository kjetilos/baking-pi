#include "timer.h"
#include <stdint.h>

const uint32_t GPIO_ADDRESS = 0x20200000;

static uint32_t * GetGpioAddress(void)
{
  return (uint32_t *) GPIO_ADDRESS;
}

void SetGpioFunction(int pin, int function)
{
  if (pin > 54 || function > 7)
    return;

  int select_register = pin / 10;
  int function_select = (pin % 10) * 3;
  
  uint32_t * addr = GetGpioAddress();
  addr[select_register] = function << function_select;
}

void SetGpio(int pin, int val)
{
  if (pin > 54)
    return;

  int set = pin / 32;
  int bit = 1 << (pin & 0x1f);

  uint32_t * addr = GetGpioAddress();

  if (val)
  {
    addr[7+set] = bit;
  }
  else
  {
    addr[10+set] = bit;
  }
}

void LedOn(void)
{
  SetGpio(16, 0);
}

void LedOff(void)
{
  SetGpio(16, 1);
}

void Blink(int times)
{
  int i;
  for (i=0; i<times; i++) {
    LedOn();
    Wait(50000);
    LedOff();
    Wait(50000);
  }
}
