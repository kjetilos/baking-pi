#include "framebuffer.h"
#include "uart.h"
#include "tag.h"
#include "drawing.h"
#include "keyboard.h"
#include "string.h"
#include "terminal.h"
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

  UsbInitialise();

  terminal_init();
  while (true)
  {
    terminal_readline();
  }

}
