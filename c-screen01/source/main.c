#include "framebuffer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int main(void)
{
  uint32_t width = 1920;
  uint32_t height = 1200;
  uint32_t depth = 32;

  SetGpioFunction(16, 1);
  struct FrameBufferInfo* fb_info = InitializeFrameBuffer(width, height, depth);

  uint32_t color = 0x1234;
  size_t y;
  size_t x;
  size_t point;
  uint32_t* fb = (uint32_t*)fb_info->pointer;

  while (true) {
    for (y=0; y<200; y++) {
      for (x=0; x<200; x++) {
	fb[y*fb_info->pitch + x] = color;
      }
    }

    color++;
    Blink(2);
  }

}
