#include "framebuffer.h"
#include "uart.h"
#include "tag.h"
#include "drawing.h"
#include "keyboard.h"
#include "string.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int arm_begin(uint32_t r0, uint32_t machtype, uint32_t atags_addr)
{
  uint32_t width = 1920;
  uint32_t height = 1200;
  uint32_t depth = 32;

  uart_init();
  uart_puts("InitializeFrameBuffer\r\n");
  struct FrameBufferInfo* fb_info = InitializeFrameBuffer(width, height, depth);
  SetFrameBufferInfo(fb_info);
  SetColor(0xff00ff00);
  DrawString("velkommen til kjetilos", 10, 20);

  uint32_t x = 20;
  uint32_t y = 10;

  char buf[20];

  while (true)
  {
    uart_puts("KeyboardUpdate\r\n");
    int addr = KeyboardUpdate();
    int_to_char(addr, buf, 10);
    uart_puts("addr=");
    uart_puts(buf);
    uart_puts("\r\n");
    char c = KeyboardGetChar();
    if (c != 0) {
      if (x >= fb_info->width) 
      {
        x = 20;
        y += 16;
      }
      if (y >= fb_info->height)
      {
        y = 10;
      }
      DrawChar(c, x, y);
      x += 8;
    } else {
      uart_puts("Null character\r\n");
    }
  }

}
