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
  
  const struct FrameBufferInfo * fb_info = InitializeFrameBuffer(width, height, depth);

  uint16_t* fb = (uint16_t*) fb_info->pointer;
  // rgb 565 
  uint16_t color = 0xcccc;
  size_t y;
  size_t x;
  size_t point;

  while (true) {
    for (point = 0; point < height*width; point++) {
      fb[point] = color;
    }
  }

}
