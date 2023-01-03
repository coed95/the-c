/* Exercise 5-2. Write getfloat, the floating-point analog of getint. */

#include <ctype.h>
#include <stdio.h>

#define		BUFSIZE		100

char buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */
int getfloat(float *pn);			/* getfloat: get next float from input into *pn */


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

int getfloat(float *pn)
{
	int c, sign;
	int decimal, division;

	while (isspace(c = getch()));
		;

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();

		if (!isdigit(c)) {
			ungetch((sign == 1) ? '+' : '-');
			return 0;
		}
	}

	if (!isdigit(c) && c != EOF && c != '.') {
		ungetch(c);
		return 0;
	}

	/* collect integer part */
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	if (c == '.') {
		c = getch();

		/* collect decimal part */
		for (decimal = 0, division = 1; isdigit(c); c = getch()) {
			decimal = 10 * decimal + (c - '0');
			division *= 10;
		}

		*pn += (float) ((float) decimal / division);
	}

	*pn *= sign;

	if (c != EOF)
	ungetch(c);

	return c;
}