/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. */

#include <stdio.h>

#define	TAB		8
#define MAXLINE 1000

int getline(char line[], int maxline);

int main(void)
{
	int i, pos, len;
	int blanks;
	char line[MAXLINE];

	pos = 1;

	while ((len = getline(line, MAXLINE)) > 0)
	{
		for (i = 0; i < len; ++i)
		{
			if (line[i] == '\n') {
				putchar(line[i]);
				pos = 1;
			}
			else if (line[i] == '\t') {
				blanks = TAB - ((pos - 1) % TAB);		/* number of blanks required */

				while (blanks > 0) {
					putchar('-');						/* should be a space ' ' but I want to track it */
					--blanks;
					++pos;
				}
			}
			else {
				putchar(line[i]);
				++pos;
			}
		}

		putchar('\n');
	}

	return 0;
}

int getline(char line[], int maxline)
{
	int i, ch;

	for (i = 0; i < maxline && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	line[i] = '\0';

	return i;
}