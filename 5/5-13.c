/*
	Exercise 5-13. Write the program tail, which prints the last n lines of its input.
	By default, n is 10, but it can be changed by an optional argument, so that
	tail -n prints the last n lines.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT		10
#define MAXLINES	1000
#define MAXLINE		1024

#define SUCCESS 	0
#define INVALID_ARG	1
#define	INVALID_NUM	2

char line[MAXLINE];

int check_arg(char []);
int getline(void);

int main(int argc, char *argv[])
{
	char *lines[MAXLINES];
	int i, len;
	int n, nlines;

	if (argc == 1)
		n = DEFAULT;
	else
	{
		if (check_arg(argv[1]) == INVALID_ARG) {
			printf("Usage: %s -n\n", argv[0]);
			return INVALID_ARG;
		}
		if (check_arg(argv[1]) == INVALID_NUM) {
			printf("%s is not a valid number\n", argv[1]);
			return INVALID_NUM;
		}

		n = strtol(++argv[1], NULL, 10);
	}

	i = 0;
	nlines = 1;

	while ((len = getline()) > 0) {
		if (strcmp(line, "quit") == 0)
			break;

		lines[i] = (char*) calloc(len, sizeof(char*));

		strncpy(lines[i++], line, len);
	}

	while (n-- > 0 && --i >= 0)
		printf("%s\n", lines[i]);

	for (i = 0; i < nlines; i++)
			free(lines[i]);

	return 0;
}

int check_arg(char arg[])
{
	int i;

	if (arg[0] != '-')
		return INVALID_ARG;

	for (i = 1; arg[i] != '\0'; i++)
		if (!isdigit(arg[i])) {
			return INVALID_NUM;
		}

	return SUCCESS;
}

int getline(void)
{
	int ch, i;
	extern char line[];

	for (i = 0; i < MAXLINE - 1 && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	line[i] = '\0';

	return i;
}