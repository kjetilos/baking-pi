#include "framebuffer.h"
#include "uart.h"
#include <stdint.h>

struct FrameBufferInfo FrameBufferInfo = {0};
static const uint32_t CHANNEL_GPU = 1;

struct FrameBufferInfo * InitializeFrameBuffer(uint32_t width, uint32_t height, uint32_t depth)
{
  if (width > 4096 || height > 4096 || depth > 32)
    return 0;
  
  FrameBufferInfo.width = width;
  FrameBufferInfo.height = height;
  FrameBufferInfo.vWidth = width;
  FrameBufferInfo.vHeight = height;
  FrameBufferInfo.pitch = 0;
  FrameBufferInfo.depth = depth;
  FrameBufferInfo.x = 0;
  FrameBufferInfo.y = 0;
  FrameBufferInfo.pointer = 0;
  FrameBufferInfo.size = 0;
  
  uart_puts("MailboxWrite\r\n");
  uint32_t value = (uint32_t)(&FrameBufferInfo) | 0x40000000;
  MailboxWrite(value, CHANNEL_GPU);

  uint32_t mail = 0;
  do {
    uart_puts("MailboxRead\r\n");
    mail = MailboxRead(CHANNEL_GPU);
  } while ((mail != 0) && (FrameBufferInfo.pointer == 0));

  return &FrameBufferInfo;
}
