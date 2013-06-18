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
  UsbInitialise();
  char buf[20];

  while (true)
  {
    uart_puts("KeyboardUpdate\r\n");
    int addr = KeyboardUpdate();
    Wait(150000);
    char c = KeyboardGetChar();
    if (c != 0) {
      uart_puts("Got character ");
      uart_putc(c);
      uart_puts("\r\n");
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
      uart_puts("No character\r\n");
    }
  }

}
