
void wait(unsigned int ticks)
{
  unsigned int* addr = (unsigned int*)0x20003000;
  unsigned int current_time = addr[1];
  unsigned int target = current_time + ticks;
  while (current_time < target) {
    current_time = addr[1];
  }
}
