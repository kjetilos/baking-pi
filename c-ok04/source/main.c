void main()
{
  int i;
  SetGpioFunction(16, 1);
  while (1) 
  {
    SetGpio(16, 1);
    wait(50000);
    SetGpio(16, 0);
    wait(50000);
  }
}
