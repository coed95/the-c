/* Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable. */

#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define BUFSIZE 100

int getop(char []);					/* getop: get next operator or numeric operand */
int getch(void);					/* get a (possibly pushed back) character */

char buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i;
	static int c = ' ';

	while (c == ' ' || c == '\t')
		c = getchar();

	s[0] = c;
	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	i = 0;

	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* collect decimal part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';

	return NUMBER;
}