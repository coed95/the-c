/* Exercise 1-11. How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any? */

#include <stdio.h>

#define		IN		1		/* inside a word */
#define		OUT		0		/* outside a word */

int main(void)
{
	int ch;
	int nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;

	while ((ch = getchar()) != EOF)
	{
		++nc;

		if (ch == '\n')
			++nl;

		if (ch == ' ' || ch == '\n' || ch == '\t') {
			state = OUT;
		}
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}

	printf("Lines: %d\nWords: %d\nChars: %d\n", nl, nw, nc);

	return 0;
}