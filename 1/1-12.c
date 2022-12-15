/* Exercise 1-12. Write a program that prints its input one word per line. */

#include <stdio.h>

#define		IN 		1
#define		OUT 	0

int main(void)
{
	int ch;
	int state = OUT;

	while ((ch = getchar()) != EOF)
	{
		if (ch != ' ' && ch != '\t' && ch != '\n') {
			state = IN;
			putchar(ch);
		}
		else if (state == IN) {
			state = OUT;
			putchar('\n');
		}
	}

	return 0;
}