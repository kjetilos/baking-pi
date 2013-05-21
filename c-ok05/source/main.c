unsigned int pattern = 0xf0f0f0f0;

void main()
{
  int pos = 0;
  int value = 0;

  SetGpioFunction(16, 1);
  while (1) 
  {
    value = pattern & (1 << pos);
    SetGpio(16, value);
    wait(50000);
  }
}
