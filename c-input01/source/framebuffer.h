#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

struct FrameBufferInfo
{
  uint32_t width;
  uint32_t height;
  uint32_t vWidth;
  uint32_t vHeight;
  uint32_t pitch;
  uint32_t depth;
  uint32_t x;
  uint32_t y;
  volatile uint32_t pointer;
  uint32_t size;
};

struct FrameBufferInfo * InitializeFrameBuffer(uint32_t width, uint32_t height, uint32_t depth);

#endif
