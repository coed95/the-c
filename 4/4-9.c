/*
	Exercise 4-9. Our getch and ungetch do not handle a pushed back EOF correctly.
	Decide what their properties ought to be if an EOF is pushed back, then implement your design.
*/

#include <stdio.h>

#define BUFSIZE	100

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */

int buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		puts("ungetch: too many characters");
	else
		buf[bufp++] = c;
}

/* EOF is defined as -1, and a char array like buf can't hold negative values.
But if the buf type is int, instead, then it can. */