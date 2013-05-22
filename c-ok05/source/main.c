#include <stdint.h>

const uint32_t PATTERN = 0xf0f0f0f0;

int main(void)
{
  int pos = 0;
  int value = 0;

  SetGpioFunction(16, 1);
  while (1) 
  {
    value = PATTERN & (1 << pos);
    SetGpio(16, value);
    Wait(50000);
  }
}
