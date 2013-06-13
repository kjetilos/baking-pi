#include <types.h>
#include <drawing.h>

u32 y = 50;

void LogPrint(char * message, u32 size)
{
	DrawString(message, 20, y);
	y += 16;
	if (y > 1024)
		y = 50;
}