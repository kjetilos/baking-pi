#include "framebuffer.h"
#include <stdint.h>


static uint32_t color = 0xffffffff;
static struct FrameBufferInfo* fb_info;

void SetColor(uint32_t c)
{
	color = c;
}

void SetFrameBufferInfo(struct FrameBufferInfo * info)
{
	fb_info = info;
}

void DrawPixel(uint32_t x, uint32_t y)
{
	if (x >= fb_info->width || y >= fb_info->height)
		return;

	uint32_t * fb = (uint32_t*) fb_info->pointer;
	uint32_t offset = y * fb_info->width + x;
	fb[offset] = color;
}

void DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
{
	int deltax, deltay;
	int stepx, stepy;

	if (x1 > x0) {
		deltax = x1 - x0;
		stepx = 1;
	} else {
		deltax = x0 - x1;
		stepx = -1;
	}

	if (y1 > y0) {
		deltay = y1 - y0;
		stepy = 1;
	} else {
		deltay = y0 - y1;
		stepy = -1;
	}

	int error = deltax - deltay;
	while (x0 != x1 && y0 != y1) {
		DrawPixel(x0, y0);

		if ( error * 2 > -deltay) {
			x0 = x0 + stepx;
			error = error - deltay;
		}
		if (error * 2 < deltax) {
			y0 = y0 + stepy;
			error = error + deltax;
		}

	}
}