void main()
{
  unsigned int * gpio = (unsigned int*)0x20200000;
  int i;
  gpio[1] = 1 << 18;
  while (1) 
  {
    gpio[10] = 1 << 16;
    for (i=0; i<0x3f0000; i++);
    gpio[7] = 1 << 16;
    for (i=0; i<0x3f0000; i++);
  }
}
