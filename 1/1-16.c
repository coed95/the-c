/* Exercise 1-16. Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text. */

#include <stdio.h>

#define		MAXLINE		1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */

int main()
{
	int len;				/* current line length */
	int max;				/* maximum length seen so far */
	char line[MAXLINE];		/* current input line */
	char longest[MAXLINE];	/* longest line saved */

	max = 0;

	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0)	/* there was a line */
		printf("%d\t\t%s", max, longest);

	return 0;
}

int getline(char line[], int maxline)
{
	int ch, i;

	for (i = 0; i < maxline && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	if (ch == '\n') {
		line[i] = ch;
		++i;
	}

	line[i] = '\0';

	return i;
}

void copy(char to[], char from[])
{
	int i;

	i = 0;

	while (from[i] != '\0')
	{
		to[i] = from[i];
		++i;
	}
}