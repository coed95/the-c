/*
	Exercise 6-1. Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines.
	Write a better version.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE		100
#define MAXWORD		100
#define NKEYS		(sizeof(keytab) / sizeof(keytab[0]))	/* number of keywords */

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

int binsearch(char *, struct key *, int);
int getword(char *, int);

/* count C keywords */
int main(void)
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
	{
		if (isalpha(word[0])) {
			n = binsearch(word, keytab, NKEYS);

			if (n >= 0)
				keytab[n].count++;
		}

		if (!strcmp(word, "quit"))
			break;
	}

	for (n = 0; n < NKEYS; n++) {
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	}

	return 0;
}

/* binsearch: find word in tab[0]...tab[n - 1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, mid, high;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		cond = strcmp(word, tab[mid].word);

		if (cond < 0)
			high = mid  - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	char *w = word;
	int c, getch(void);
	void ungetch(int);

	int in_comment = 0;		/* 1 if inside a comment */
	int in_pp_line = 0;		/* 1 if inside a preprocessor line */
	int in_string = 0;		/* 1 if inside a string */

	/* skip spaces */
	while (isspace(c = getch()))
		;

	if (c != EOF)
		*w++ = c;

	/* not underscore, pp line, comment, string */
	if (!isalpha(c) && c != '_' && c != '\"' && c != '#' && c != '/') {
		*w = '\0';
		return c;
	}

	if (c == '\"')
		in_string = 1;

	if (c == '#')
		in_pp_line = 1;

	/* it only checks single line comments for now */
	if (c == '/') {
		if ((c = getch()) == '/')
			in_comment = 1;
		else
			ungetch(c);
	}

	while (--lim > 0)
	{
		c = getch();

		if (in_comment && (c == '\n'))
			in_comment = 0;

		if (in_pp_line && (c == '\n'))
			in_pp_line = 0;

		/* if the char is in a string or in a pp line, and is not alphanumeric */
		if (!isalnum(c) && c != '_' && (in_string == 1 || c != '\"') && !in_pp_line && !in_comment)
		{
			ungetch(c);
			break;
		}

		if (c == '/' && *(w - 1) == '/')
			in_comment = 1;

		if (c == '\"')
			in_string = (in_string == 1) ? 0 : 1;

		*w++ = c;
	}

	*w = '\0';

	return word[0];
}

/* get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}