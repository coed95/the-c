#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dcl.h"

int tokentype;					/* type of last token */
char token[MAXTOKEN];			/* last token string */
char name[MAXTOKEN];			/* identifier name */
char datatype[MAXTOKEN];		/* data type = char, int, etc. */
char out[MAXOUTPUT];			/* output string */

char buf[BUFSIZE];				/* buffer for ungetch */
int bufp = 0;					/* next free position in buf */

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

		if (tokentype != ')')
			printf("error: missing ')'\n");
	}
	else if (tokentype == NAME)	/* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");

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