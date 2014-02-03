#include <stdio.h>
#include <stdint.h>

extern unsigned char _binary_sound_end;
extern unsigned char _binary_sound_size;
extern unsigned char _binary_sound_start;

int fifo;

void push(uint16_t value)
{
  fifo = value;
  printf("%x \n", value);
}

void play(void)
{
  const uint16_t * data = (uint16_t *)&_binary_sound_start;
  const uint16_t * end = (uint16_t *)&_binary_sound_end;

  while (data < end)
  {
    push(*data);
    data++;
  }
}


int main(void)
{
  play();
}
