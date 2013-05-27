#include "framebuffer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int main(void)
{
  uint32_t width = 1024;
  uint32_t height = 768;
  uint32_t depth = 16;

  SetGpioFunction(16, 1);
  LedOn();
  Wait(50000);
  uint16_t* fb = InitializeFrameBuffer(width, height, depth);

  LedOn();
  while (fb == 0) {
    Blink(1);
    Wait(100000);
  }

  // rgb 565 
  uint16_t color = 0x1234;
  size_t y;
  size_t x;
  size_t point;

  while (true) {
    for (point = 0; point < height*width; point++) {
      fb[point] = color;
    }
    color++;
    Blink(2);
  }

}
