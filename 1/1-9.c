/* Exercise 1-9. Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. */

#include <stdio.h>

int main(void)
{
	int ch;
	int blanks;

	blanks = 0;

	while ((ch = getchar()) != EOF)
	{
		if (ch == ' ')
		{
			++blanks;

			if (blanks == 1)
				putchar(ch);
		}

		if (ch != ' ')
		{
			blanks = 0;
			putchar(ch);
		}
	}

	return 0;
}