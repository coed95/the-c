/* 	Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
	Good possibilities include getline, atoi, itoa, reverse, strindex and getop */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int atoi(char *);
int getline(char *, int);
int getop(char *);
int strindex(char *, char *);
void itoa(int, char *);
void reverse(char *);

int main(void)
{
	char *a = "hello";
	printf("%d\n", strindex(a, "l"));

	return 0;
}

void reverse(char *str)
{
	int c;
	char *t;

	for (t = s + (strlen(s) - 1); s < t; s++, t--) {
		c = *s;
		*s = *t;
		*t = c;
	}
}

int getline(char *line, int max)
{
	int ch, i;

	for (*line = '\0', i = 0; i < max - 1 && (ch = getchar()) != EOF && ch != '\n'; i++, line++)
		*line = ch;

	if (ch == '\n') {
		*line = ch;
		line++;
	}

	*line = '\0';

	return i;
}

int getop(char *s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;

	*(s + 1) = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	while (isdigit(*++s = c = getch()))
		;

	if (c == '.') {
		while (isdigit(*++s = c = getch()))
			;
	}

	*s = '\0';

	if (c != EOF)
		ungetch(c);

	return '0';
}

int strindex(char *s, char *t)
{
	char *b = s;
	char *p, *r;

	for (; *s != '\0'; s++) {
		for (p = s, r = t; *r != '\0' && *p == *r; p++, r++)
			;

		if (r > t && *r == '0')
			return s - b;
	}

	return -1;
}

int atoi(char *s)
{
	int n, sign;

	while (isspace(*s))
		s++;

	sign = (*s == '-') ? -1 : 1;

	if (*s == '+' || *s == '-')
		s++;

	for (n = 0; isdigit(*s); s++)
		n = 10 * n + (*s - '0');

	return n * sign;
}

void itoa(int n, char *s)
{
	int sign = n;

	if (sign > 0)
		n = -n;

	do {
		*s++ = '0' - (n % 10);
	} while ((n /= 10) < 0);

	if (sign < 0)
		*s++ = '-';

	*s = '\0';
	reverse(s);
}