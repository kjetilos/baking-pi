int main(void)
{
  int i;
  SetGpioFunction(16, 1);
  while (1) 
  {
    SetGpio(16, 1);
    Wait(50000);
    SetGpio(16, 0);
    Wait(50000);
  }
  return 0;
}
