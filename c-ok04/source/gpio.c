const unsigned int const * GPIO_ADDRESS = (unsigned int*) 0x20200000;

unsigned int* GetGpioAddress(void)
{
  return (unsigned int*) GPIO_ADDRESS;
}

void SetGpioFunction(int pin, int function)
{
  if (pin > 54 || function > 7)
    return;

  int select_register = pin / 10;
  int function_select = pin % 10;
  
  unsigned int * addr = GetGpioAddress();
  addr[select_register] = function << function_select;
}

void SetGpio(int pin, int val)
{
  if (pin > 54)
    return;

  int set = pin / 32;
  int bit = 1 << (pin & 0x1f);

  unsigned int * addr = GetGpioAddress();

  if (val)
  {
    addr[7 + set] = bit;
  }
  else
  {
    addr[10 + set] = bit;
  }
}

