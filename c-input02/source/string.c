#include "string.h"
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

static char table[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f',
};

void reverse(char * buffer, uint32_t length)
{
	char * start = buffer;
	char * end = buffer + length - 1;
	while (end > start) 
	{
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
}

uint32_t uint_to_char(uint32_t number, char * buffer, uint32_t base)
{
	int length = 0;
	while (number > 0)
	{
		uint32_t rest = number % base;
		number = number / base;
		buffer[length] = table[rest];
		length++;
	}

	reverse(buffer, length);
	buffer[length] = 0;
	return length;
}

uint32_t int_to_char(int32_t number, char * buffer, uint32_t base)
{
	if (number >= 0)
	{
		return uint_to_char(number, buffer, base);
	}
	else
	{
		buffer[0] = '-';
		return uint_to_char(-number, buffer+1, base);
	}
}

uint32_t displayf(char * format, char * dest, ...)
{
	va_list args;

	union {
		char c;
		int i;
		char * s;
		int * p;
	} arg;

	int index = 0;
	int length = 0;
	char c;

	va_start(args, dest);
	while ((c = format[index]) != 0)
	{
		if (c == '%')
		{
			index++;
			c = format[index];
			switch (c) {
			case '%': 
				dest[length] = '%';
				length++;
				break;
			case 'c':
				arg.c = va_arg(args, int);
				dest[length] = arg.c;
				length++;
				break;
			case 'd':
			case 'i':
				arg.i = va_arg(args, int);
				length += int_to_char(arg.i, dest+length, 10);
				break;
			case 'o':
				arg.i = va_arg(args, int);
				length += uint_to_char(arg.i, dest+length, 8);
				break;
			case 'u':
				arg.i = va_arg(args, int);
				length += uint_to_char(arg.i, dest+length, 10);
				break;
			case 'b':
				arg.i = va_arg(args, int);
				length += uint_to_char(arg.i, dest+length, 2);
				break;
			case 'x':
				arg.i = va_arg(args, int);
				length += uint_to_char(arg.i, dest+length, 16);
				break;
			case 's':
				arg.s = va_arg(args, char *);
				while (*arg.s != '\0')
				{
					dest[length] = *arg.s;
					length++;
					arg.s++;
				}
				break;
			case 'n':
				arg.p = va_arg(args, int *);
				*arg.p = length;
				break;				
			}
		}
		else
		{
			dest[length] = c;
			length++;
		}
		index++;
	}
	va_end(args);

	dest[length] = '\0';
	length++;
	return length;
}

void * memcpy(void *dest, const void *src, size_t n)
{
	uint8_t * d = dest;
	const uint8_t * s = src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return dest;
}