/* Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. */

#include <stdio.h>
#include <string.h>

#define	MAXLEN		1000
#define MAXLINES	5000

int readlines(char *lineptr[], int);

int main(void)
{
	char *lines[MAXLINES];

	readlines(lines, MAXLINES);

	return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, lines;

	nlines = 0;

	while ((len = getline(lineptr[nlines], MAXLEN)) > 0) {
		if (nlines >= maxlines)
			return -1;
		else {
			lineptr[nlines++] = '\0';
		}
	}

	return nlines;
}