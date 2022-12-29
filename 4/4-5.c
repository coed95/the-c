/*
	Exercise 4-5. Add access to library functions like sin, exp, and pow.
*/

#include <math.h>					/* fmod(), sin(), exp() and pow() */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>					/* atof() */
#include <string.h>

#define		BUFSIZE		100
#define		MAXOP		100			/* max size of operand or operator */
#define		MAXVAL		100			/* max depth of value stack */
#define		NUMBER		'0'			/* signal that a number was found */
#define		FUNCTION	'1'			/* function found */

int getch(void);					/* get a (possibly pushed back) character */
void ungetch(int);					/* ungetch: push a character back on input */
int getop(char []);					/* getop: get next operator or numeric operand */
void push(double);					/* push a value onto stack */
double pop(void);					/* pop and return top value from stack */
void funclib(char []);				/* recognize one of the supported math functions */

char buf[BUFSIZE];					/* buffer for ungetch */
int bufp = 0;						/* next free position in buf */

int sp = 0;							/* next free stack position */
double val[MAXVAL];					/* value on the stack */

int main(void)
{
	int type, p = 0;
	int temp;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)
	{
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case FUNCTION:
				funclib(s);
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

			/* clear the stack */
			case '!':
				while (sp != 0)
					val[sp--] = 0;
				break;

			/* swap top two elements */
			case '~':
				temp = pop();
				op2 = pop();

				push(temp);
				push(op2);

				break;

			/* duplicate top element */
			case '#':
				op2 = pop();
				push(op2);
				push(op2);
				break;

			/* print top element */
			case '?':
				p = 1;
				break;

			case '\n':
				if (!p)
					printf("%.8g\n", pop());
				else {
					printf("%.8g\n", val[sp - 1]);
					p = 0;
				}
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

	/* if there is a function name */
	if (isalpha(c))
	{
		i = 0;
		while (isalpha(s[i++] = c))
			c = getch();
		s[i - 1] = '\0';

		if (c != EOF)
			ungetch(c);

		return FUNCTION;
	}

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

void funclib(char s[])
{
	double op2;

	if (strcmp(s, "cos") == 0)
		push(cos(pop()));
	else if(strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "pow") == 0)
	{
		op2 = pop();
		push(pow(pop(), op2));
	}
	else
		printf("error: unknown function %s\n", s);
}