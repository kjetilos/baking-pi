# 1 "source/main.c"
# 1 "<command-line>"
# 1 "source/main.c"
void main()
{
  unsigned char * gpio = (unsigned char*)0x20200000;
  gpio[4] = 1 << 18;
  gpio[40] = 1 << 16;
  while (1);
}
