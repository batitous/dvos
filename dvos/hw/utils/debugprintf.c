
#include "../include/libs-hardware.h"

#include <stdarg.h>

void defaultDebugInterface(UInt8 c)
{
    c = 0;
}

static DebugInterfaceCallback debugInterfaceCallback = &defaultDebugInterface;

void xputc(UInt8 c)
{
    debugInterfaceCallback(c);
}

void xputs (const char* str)
{
	while (*str)
	{
		xputc(*str++);
	}
}

void SetDebugInterface(DebugInterfaceCallback callback)
{
    debugInterfaceCallback = callback;
}

void DebugPrintf (
	const char*	str,	// Pointer to the format string
	...					// Optional arguments
)
{
	va_list arp;
	unsigned int r, i, w, f;
	unsigned long val;
	char s[16], c, d;


	va_start(arp, str);

	while ((c = *str++) != 0) {
		if (c != '%') {
			xputc(c); continue;
		}
		c = *str++;
		f = 0;
		if (c == '0') {				// Flag: '0' padded
			f = 1; c = *str++;
		}
		w = 0;
		while (c >= '0' && c <= '9') {	// Minimum width
			w = w * 10 + c - '0';
			c = *str++;
		}
		if (c == 'l' || c == 'L') {	// Prefix: Size is long int
			f |= 2; c = *str++;
		}
		if (!c) break;
		d = c;
		if (d >= 'a') d -= 0x20;
		switch (d) {				// Type is...
		case 'S' :					// String
			xputs(va_arg(arp, char*)); continue;
		case 'C' :					// Character
			xputc((char)va_arg(arp, int)); continue;
		case 'B' :					// Binary
			r = 2; break;
		case 'O' :					// Octal
			r = 8; break;
		case 'D' :					// Signed decimal
		case 'U' :					// Unsigned decimal
			r = 10; break;
		case 'X' :					// Hexdecimal
			r = 16; break;
		default:					// Unknown
			xputc(c); continue;
		}

		// Get an argument and put it in numeral
		if (f & 2) {
			val = va_arg(arp, long);
		} else {
			if (d == 'D') {
				val = (long)va_arg(arp, int);
			} else {
				val =va_arg(arp, unsigned int);
			}
		}
		if (d == 'D' && (val & 0x80000000)) {
			val = 0 - val;
			f |= 4;
		}
		i = 0;
		do {
			d = (char)(val % r); val /= r;
			if (d > 9) {
				d += 7;
				if (c == 'x') d += 0x20;
			}
			s[i++] = d + '0';
		} while (val && i < sizeof(s));
		if (f & 4) s[i++] = '-';
		while (i < w--) xputc((f & 1) ? '0' : ' ');
		do xputc(s[--i]); while(i);
	}

	va_end(arp);
}

/*
#define putchar(c) SendByteToUART0(c)

static void printchar(char **str, int c)
{
	extern int putchar(int c);
	if (str) {
		**str = c;
		++(*str);
	}
	else (void)putchar(c);
}

#define PAD_RIGHT 1
#define PAD_ZERO 2

static int prints(char **out, const char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';

	if (width > 0) {
		register int len = 0;
		register const char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			printchar (out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		printchar (out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		printchar (out, padchar);
		++pc;
	}

	return pc;
}

// the following should be enough for 32 bit int
#define PRINT_BUF_LEN 12

static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints (out, print_buf, width, pad);
	}

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg) {
		if( width && (pad & PAD_ZERO) ) {
			printchar (out, '-');
			++pc;
			--width;
		}
		else {
			*--s = '-';
		}
	}

	return pc + prints (out, s, width, pad);
}

static int print(char **out, int *varg)
{
	register int width, pad;
	register int pc = 0;
	register char *format = (char *)(*varg++);
	char scr[2];

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0') break;
			if (*format == '%') goto out;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
			for ( ; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if( *format == 's' ) {
				register char *s = *((char **)varg++);
				pc += prints (out, s?s:"(null)", width, pad);
				continue;
			}
			if( *format == 'd' ) {
				pc += printi (out, *varg++, 10, 1, width, pad, 'a');
				continue;
			}
			if( *format == 'x' ) {
				pc += printi (out, *varg++, 16, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'X' ) {
				pc += printi (out, *varg++, 16, 0, width, pad, 'A');
				continue;
			}
			if( *format == 'u' ) {
				pc += printi (out, *varg++, 10, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'c' ) {
				// char are converted to int then pushed on the stack
				scr[0] = *varg++;
				scr[1] = '\0';
				pc += prints (out, scr, width, pad);
				continue;
			}
		}
		else {
		out:
			printchar (out, *format);
			++pc;
		}
	}
	if (out) **out = '\0';
	return pc;
}


int DebugPrintf(const char *format, ...)
{
	register int *varg = (int *)(&format);
	return print(0, varg);
}

int DebugSprintf(char *out, const char *format, ...)
{
	register int *varg = (int *)(&format);
	return print(&out, varg);
}
*/
