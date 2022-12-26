/*
	Exercise 3-5. Write the function itob(n, s, b) that converts the integer n into a base b character representation in the string s. In particular, itob(n, s, 16) formats n as a hexadecimal integer in s. (For now I just made it for unsigned ints only)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE_TO_BINARY(byte)   \
	(byte & 0x80 ? '1' : '0'), \
	(byte & 0x40 ? '1' : '0'), \
	(byte & 0x20 ? '1' : '0'), \
	(byte & 0x10 ? '1' : '0'), \
	(byte & 0x08 ? '1' : '0'), \
	(byte & 0x04 ? '1' : '0'), \
	(byte & 0x02 ? '1' : '0'), \
	(byte & 0x01 ? '1' : '0')

void reverse(char s[]);
void uitob(unsigned int n, char s[], int b);

int main(void)
{
	int n = 7;
	char s[1024];

	uitob(n, s, 2);
	printf("%s\n", s);

	return 0;
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void uitob(unsigned int n, char s[], int b)
{
	switch (b) {
		case 2:
			sprintf(s, "\0");

			for (; n != 0; n >>= 1)
				strcat(s, (n & 1) ? "1" : "0");

			reverse(s);
			break;
		case 8:
			sprintf(s, "%o", n);
			break;
		case 10:
			sprintf(s, "%d", n);
			break;
		case 16:
			sprintf(s, "%0x", n);
			break;
	}
}