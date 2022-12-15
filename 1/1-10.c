/* Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way. */

#include <stdio.h>

int main(void)
{
	int ch;

	while ((ch = getchar()) != EOF)
	{
		switch (ch)
		{
			case '\t':
				printf("\\t");
				break;

			case '\b':
				printf("\\b");
				break;

			case '\\':
				printf("\\\\");
				break;

			default:
				putchar(ch);
		}
	}

	return 0;
}