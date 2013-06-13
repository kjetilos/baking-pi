#ifndef DRAWING_H
#define DRAWING_H

#include "framebuffer.h"
#include <stdint.h>

void SetColor(uint32_t c);
void SetFrameBufferInfo(struct FrameBufferInfo * info);
void DrawPixel(uint32_t x, uint32_t y);
void DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void DrawChar(char c, uint32_t x, uint32_t y);
void DrawString(const char * s, uint32_t x, uint32_t y);

#endif
