#include "framebuffer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int main(void)
{
  uint32_t width = 1920;
  uint32_t height = 1200;
  uint32_t depth = 24;

  SetGpioFunction(16, 1);
  struct FrameBufferInfo* fb_info = InitializeFrameBuffer(width, height, depth);

  uint32_t color = 0x1234;
  size_t y;
  size_t x;
  size_t point;
  uint32_t* fb = (uint32_t*)fb_info->pointer;

  while (true) {
    for (point = 0; point < height*width; point++) {
      fb[point] = color;
    }
    color++;
    Blink(2);
  }

}
