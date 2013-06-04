#include "framebuffer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <uart.h>

/**
 * How is the color components represented for 16, 24 and 32 bit color depth
 * 
 * RGB 565
 * ------------
 *  Red   = 0xf800 >> 11
 *  Green = 0x07e0 >> 5
 *  Blue  = 0x001f >> 0
 * 
 * ARGB 8888
 * ------------
 *  Alpha = 0xff000000 >> 24
 *  Red   = 0x00ff0000 >> 16
 *  Green = 0x0000ff00 >> 8
 *  Blue  = 0x000000ff >> 0
 *
 * RGB 888
 * ---------
 *  Red   = 0x00ff0000 >> 16
 *  Green = 0x0000ff00 >> 8
 *  Blue  = 0x000000ff >> 0
 *
 */
int main(void)
{
  uint32_t width = 1920;
  uint32_t height = 1200;
  uint32_t depth = 32;

  uart_init();
  uart_puts("InitializeFrameBuffer\r\n");
  struct FrameBufferInfo* fb_info = InitializeFrameBuffer(width, height, depth);

  uint32_t seed = 0;
  uart_puts("Painting\r\n");

  SetFrameBufferInfo(fb_info);
  while (true) {
    uint32_t x0 = NextRandom() % 400;
    uint32_t y0 = NextRandom() % 400;
    uint32_t x1 = NextRandom() % 400;
    uint32_t y1 = NextRandom() % 400;
    uint32_t color = NextRandom() | 0xff000000;
    SetColor(color);
    DrawLine(x0, y0, x1, y1);
  }

}
