/*
	Exercise 4-7. Write a routine ungets(s) that will push back
	an entire string onto the input. Should ungets know about
	buf and bufp, or should it use ungetch?
*/

#include <stdio.h>
#include <string.h>

#define BUFSIZE	100

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */
void ungets(char []);				/* ungets: push a string back on input */

char buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

int main(void)
{
	char str[] = "hello world";
	int c;

	ungets(str);

	while ((c = getch()) != EOF) {
		putchar(c);
	}

	return 0;
}

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

void ungets(char str[])
{
	int len;

	for (len = strlen(str) - 1; len >= 0; len--)
		ungetch(str[len]);
}