#include "framebuffer.h"
#include "uart.h"
#include "tag.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int main(uint32_t r0, uint32_t machtype, uint32_t atags_addr)
{
  uint32_t width = 1920;
  uint32_t height = 1200;
  uint32_t depth = 32;

  uart_init();
  uart_puts("InitializeFrameBuffer\r\n");
  struct FrameBufferInfo* fb_info = InitializeFrameBuffer(width, height, depth);

  uint32_t seed = 0;
  uart_puts("Painting\r\n");

  atag_init(atags_addr);
  struct tag cmd_line = atag_get(0x54410009);

  SetFrameBufferInfo(fb_info);
  while (true) {
    SetColor(0xff00ff00);
    DrawString("velkommen til kjetilos", 500,500);
    if (cmd_line.data != 0)
    {
      DrawString((char *)cmd_line.data, 500, 600);
    }
    else
    {
      DrawString("no cmd_line", 500, 600);
    }
  }

}
