/* Exercise 5-1. As written, getint treat a + or - not followed by a digit as a valid representation of zero.
Fix it to push such a character back on the input. */

#include <ctype.h>

#define		BUFSIZE		100

char buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */
int getint(int *pn);				/* getint: get next integer from input into *pn */

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int ch)
{
	if (bufp >= BUFSIZE)
		puts("error: too many characters");
	else
		buf[bufp++] = ch;
}

int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))	/* skip white spaces */
		;

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();

		if (!isdigit(c)) {
			ungetch((sign == 1) ? '+' : '-');
			return 0;
		}
	}

	if (!isdigit(c) && c != EOF)
	{
		ungetch(c);		/* not a number */
		return 0;
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}