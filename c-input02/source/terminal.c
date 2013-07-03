#include "drawing.h"
#include "keyboard.h"
#include <stdint.h>

// (1920/8) 240 x (1200/16)75 character terminal
uint32_t terminal_width = 240;
uint32_t terminal_height = 75;
char terminal_screen[240 * 75] = {0};

void terminal_init()
{
}

void terminal_display()
{
	uint32_t x, y;
	for (x=0; x<terminal_width; x++) {
		for (y=0; y<terminal_height; y++) {
			char c = terminal_screen[y*terminal_width + x];
			DrawChar(c, x*8, y*16);
		}
	}	
}

void terminal_readline()
{
	uint32_t x = 0;
	uint32_t y = 0;

	while (1) 
	{
		KeyboardUpdate();
		char c = KeyboardGetChar();

		if (c == 0)
			continue;

		terminal_screen[y*terminal_width + x] = c;
		if (c == '\n') 
		{
			y++;
			y = y % 75;
			x = 0;
		}
		else
		{
			x++;
			x = x % 240;
		}

		terminal_display();
	}

}