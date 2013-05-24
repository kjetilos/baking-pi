#include "framebuffer.h"
#include <stdint.h>

struct FrameBufferInfo FrameBufferInfo;
static const uint32_t CHANNEL_GPU = 1;

const struct FrameBufferInfo* InitializeFrameBuffer(uint32_t width, uint32_t height, uint32_t depth)
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
  
  LedOff();
  MailboxWrite(&FrameBufferInfo, CHANNEL_GPU);
  Blink(1);

  uint32_t mail = MailboxRead(CHANNEL_GPU);
  Blink(2);

  if (mail == 0)
    return 0;

  /* Wait for the GPU filling in the framebuffer pointer */
  LedOff();
  while (FrameBufferInfo.pointer == 0) ;
  LedOn();

  return & FrameBufferInfo;
}
