void main()
{
  int i;
  SetGpioFunction(16, 1);
  while (1) 
  {
    SetGpio(16, 1);
    for (i=0; i<0x3f0000; i++);
    SetGpio(16, 0);
    for (i=0; i<0x3f0000; i++);
  }
}
