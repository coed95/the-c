/*
	Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator.
	Add the modulus (%) operator and provisions for negative numbers.
*/

#include <math.h>					/* fmod() */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>					/* atof() */

#define		BUFSIZE		100
#define		MAXOP		100			/* max size of operand or operator */
#define		MAXVAL		100			/* max depth of value stack */
#define		NUMBER		'0'			/* signal that a number was found */

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */

int getop(char []);					/* getop: get next operator or numeric operand */

void push(double);					/* push a value onto stack */
double pop(void);					/* pop and return top value from stack */

char buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

int sp = 0;							/* next free stack position */
double val[MAXVAL];					/* value on the stack */

int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)
	{
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();

				if (op2 == 0)
					puts("error: zero division");
				else
					push(pop() / op2);
				break;
			case '%':
				op2 = pop();

				if (op2 == 0)
					puts("error: zero division");
				else
					push(fmod(pop(), op2));
				break;
			case '\n':
				printf("%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}		
	}

	return 0;
}

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

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	i = 0;

	/* if there is '-' followed by a digit, then the number is negative */
	if (c == '-' && !isdigit(s[++i] = c = getch())) {
		ungetch(c);
		c = s[0];
	}

	/* if c is not a number */
	if (!isdigit(c) && c != '.')
		return c;

	/* collect integer part */
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;

	/* collect fraction part */
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';

	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, cannot push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
		return 0.0;
}