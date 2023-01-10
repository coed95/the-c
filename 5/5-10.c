/*
	Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example,

	expr 2 3 4 + -

	evaluates 2 x (3 + 4).
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVALUE		100
#define NUMBER			'0'

/* The statement below disables MinGW globbing, so that you can use * rather than x */
/* extern int _CRT_glob = 0; */

void push(double);
double pop(void);

double value[MAXVALUE];
short sp = 0;

int main(int argc, char *argv[])
{
	int i, type;
	double number, op2;

	if (argc == 1) {
		printf("Usage: %s <expression>\n", *argv);
		return 1;
	}

	for (i = 1; i < argc; i++)
	{
		switch (argv[i][0]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				number = strtod(argv[i], NULL);
				push(number);
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case 'x':	/* x instead of * because of the shell wildcard :^) */
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();

				if (op2 == 0.0) {
					puts("Error: zero division");
					return 1;
				}

				push(pop() / op2);
				break;
		}
	}

	printf("%.2g\n", pop());

	return 0;
}

void push(double f)
{
	if (sp < MAXVALUE)
		value[sp++] = f;
	else
		printf("Error: stack is full, cannot push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return value[--sp];
	else
		return 0.0;
}