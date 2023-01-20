/* Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE		100
#define	MAXTOKEN	100
#define MAXOUTPUT	1000

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);

int getch(void);
void ungetch(int);

int tokentype;				/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[MAXOUTPUT];		/* output string */
int previous_token;			/* previous token before the error */

char buf[BUFSIZE];			/* buffer for ungetch */
int bufp = 0;				/* next free position in buf */

/* convert word description to declaration */
int main(void)
{
	int c, i;
	int ptrcount;			/* counts the number of '*' */
	int type;
	char temp[MAXTOKEN];
	char *ptr = NULL;

	while (gettoken() != EOF) {
		strcpy(out, token);
		ptrcount = 0;

		while ((type = gettoken()) != '\n')
		{
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				ptrcount++;

				while ((c = getch()) == '*' || c == ' ') {
					if (c == '*')
						ptrcount++;
					else
						break;
				}
				ungetch(c);

				for (i = 0, ptr = calloc(ptrcount, sizeof(char*)); i < ptrcount; i++)
					ptr[i] = '*';
				ptr[i] = '\0';

				snprintf(temp, MAXTOKEN, "(%s%s)", ptr, out);
				strncpy(out, temp, MAXOUTPUT);
				free(ptr);
			}
			else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
		}

		printf("%s\n", out);
	}

	return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; ns++)	/* count *'s */
		;

	dirdcl();

	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;

	if (tokentype == '(')		/* dcl */
	{
		dcl();

		if (tokentype != ')') {
			printf("error: missing ')'\n");
			previous_token = 1;
		}
	}
	else if (tokentype == NAME)	/* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		previous_token = 1;
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

/* return next token (skip blanks and tabs) */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	/* return the previous token in case of input error */
	if (previous_token) {
		previous_token = 0;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t')
		;

	if (c == '(')
	{
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[')
	{
		for (*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';

		return tokentype = BRACKETS;
	}
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;

		*p = '\0';
		ungetch(c);

		return tokentype = NAME;
	}
	else
		return tokentype = c;
}

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		puts("ungetch: too many characters");
	else
		buf[bufp++] = c;
}