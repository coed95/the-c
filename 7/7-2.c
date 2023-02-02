/*
	Exercise 7-2. Write a program that will print arbitrary input in a sensible way.
	As a minimum, it should print non-graphic characters in octal or hexadecimal, and break long text lines.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN				10		/* max line length */
#define N_ARGS				2

#define invalid_arg(x)		(strcmp(x, "-o") && strcmp(x, "-h"))

int main(int argc, char *argv[])
{
	int c, n;
	char *fmt;

	if (argc != N_ARGS) {
		printf("Usage: %s -o/-h\n", argv[0]);
		return 1;
	}

	if (invalid_arg(argv[1])) {
		printf("Error: invalid argument %s\n", argv[1]);
		return 1;
	}

	fmt = (strcmp(argv[1], "-h")) ? "%x " : "%o ";
	n = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
			n = 0;
		else if (n == MAXLEN) {
			n = 0;
			putchar('\n');
		}

		if (isgraph(c) || isspace(c))
			putchar(c);
		else
			printf(fmt, c);

		n++;
	}

	return 0;
}