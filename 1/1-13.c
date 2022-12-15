/* Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. */

#include <stdio.h>

#define   	IN      1
#define   	OUT     0
#define		MAX		100

int main(void)
{
	int ch, state;
	int i, index, wlen;
	int histogram[MAX];

	state = OUT;
	wlen = 0;

	for (index = 0; index < MAX; ++index)
	{
		histogram[index] = 0;
	}

	index = 0;

	while ((ch = getchar()) != EOF)
	{
		if (ch != ' ' && ch != '\t' && ch != '\n') {
			state = IN;
			histogram[index] = ++wlen;
			putchar(ch);
		}
		else if (state == IN) {
			state = OUT;
			wlen = 0;

			printf("\t\t\t\t\t");

			for (i = 0; i < histogram[index]; i++)
				putchar('|');

			putchar('\n');
			++index;

			if (index > MAX)
				break;
		}
	}

	return 0;
}

