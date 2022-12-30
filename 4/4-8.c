/*
	Exercise 4-8. Suppose that there will never be more than one character of pushback.
	Modify getch and ungetch accordingly.
*/

#include <stdio.h>

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */

int buf = EOF;						/* buffer for ungetch (only one char this time) */

int getch(void)
{
	int tmp;

	if (buf == EOF)
		tmp = getchar();
	else {
		tmp = buf;
		buf = EOF;
	}

	return tmp;
}

void ungetch(int c)
{
	if (buf == EOF)
		buf = c;
	else
		puts("ungetch: too many characters");
}