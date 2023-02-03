/*
	Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion.
*/

#include <math.h>
#include <stdio.h>
#include <string.h>

#define	MAXOP	100		/* max size of operand or operator */
#define	MAXVAL	200		/* max depth of value stack */

#define is_op(x) (\
	(x == '+') || \
	(x == '-') || \
	(x == 'x') || \
	(x == '/'))

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

void push(double f);
double pop(void);

int main(void)
{
	char expr[MAXOP];
	int ch;
	double op, num;

	while (scanf("%99s%c", expr, &ch) == 2)
	{
		if (sscanf(expr, "%lf", &num) == 1) {
			/* number found */
			push(num);
		}
		else if (!is_op(*expr)) {
			/* not a valid operator */
			printf("%s is not a valid operator\n", expr);
		}
		else {
			switch (*expr) {
				case '+':
					push(pop() + pop());
					break;
				case '-':
					op = pop();
					push(pop() - op);
					break;
				case 'x':
					push(pop() * pop());
					break;
				case '/':
					op = pop();

					if (op == 0)
						printf("error: zero division\n");
					else
						push(pop() / op);

					break;
			}
		}

		if (ch == '\n')
			printf("%.8g\n", pop());
	}

	return 0;
}

/* push: push f onto value stack */
void push(double f)
{
	if (sp >= MAXVAL)
		printf("error: stack full, cannot push %f\n", f);
	else
		val[sp++] = f;
}

/* pop: return top value from stack */
double pop(void)
{
	return (sp > 0) ? val[--sp] : 0.0;
}