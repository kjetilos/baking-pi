#include "keyboard.h"
#include <device/hid/keyboard.h>
#include <usbd/usbd.h>

int KeyboardAddress = 0;
int KeyDown[6] = {0,0,0,0,0,0};

char KeysNormal[] = {
 0x0, 0x0, 0x0, 0x0, 'a', 'b', 'c', 'd',
 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
 '3', '4', '5', '6', '7', '8', '9', '0',
 '\n', 0x0, '\b', '\t', ' ', '-', '=', '[',
 ']', '\\', '#', ';', '\'', '`', ',', '.',
 '/', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+',
 '\n', '1', '2', '3', '4', '5', '6', '7',
 '8', '9', '0', '.', '\\', 0x0, 0x0, '=',
};

char KeysShift[] = {
 0x0, 0x0, 0x0, 0x0, 'A', 'B', 'C', 'D',
 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '"',
 '£', '$', '%', '^', '&', '*', '(', ')',
 '\n', 0x0, '\b', '\t', ' ', '_', '+', '{',
 '}', '|', '~', ':', '@', '¬', '<', '>',
 '?', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+',
 '\n', '1', '2', '3', '4', '5', '6', '7',
 '8', '9', '0', '.', '|', 0x0, 0x0, '='
};

int KeyboardUpdate()
{
	do
	{
		if (KeyboardAddress == 0) 
		{
			UsbCheckForChange();
			if (KeyboardCount() == 0) 
			{
				KeyboardAddress = 0;
				return 0;
			}
		
			KeyboardAddress = KeyboardGetAddress(0);
			if (KeyboardAddress == 0)
			{
				return 0;
			}
		}

		int i;
		for (i=0; i<6; i++) 
		{
			KeyDown[i] = KeyboardGetKeyDown(KeyboardAddress, i);
		}
	} while (KeyboardPoll(KeyboardAddress) != 0);
	return KeyboardAddress;
}

int KeyWasDown(int key) 
{
	int i;
	for (i=0; i<6; i++) 
	{
		if (KeyDown[i] == key)
			return 1;
	}
	return 0;
}

char KeyboardGetChar()
{
	if (KeyboardAddress == 0)
		return 0;

	int i;
	for (i=0; i<6; i++) 
	{
		int key = KeyboardGetKeyDown(KeyboardAddress, i);
		if (key == 0)
			break;

		if (KeyWasDown(key))
			continue;

		if (key > 103)
			continue;

		char * table = KeysNormal;
		struct KeyboardModifiers modifiers = KeyboardGetModifiers(KeyboardAddress);
		if (modifiers.LeftShift || modifiers.RightShift)
			table = KeysShift;

		char value = table[key];
		if (value != 0)
			return value;
	}
	return 0;
}

