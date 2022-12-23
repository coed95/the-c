/* Exercise 3-2. Write a function escape(s, t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters. */

#include <stdio.h>

#define MAXLINE 1024

int getline(char line[], int maxline);
void escape(char dest[], char str[]);
void unescape(char dest[], char str[]);

int main(void)
{
	char dest[MAXLINE];
	char dest2[MAXLINE];
	char str[MAXLINE];

	getline(str, MAXLINE);
	printf("Starting string: %s", str);

	escape(dest, str);
	printf("String after escape: %s\n", dest);

	unescape(dest2, dest);
	printf("String after unescape: %s", dest2);

	return 0;
}

int getline(char line[], int maxline)
{
	int i, ch;

	for (i = 0; i < maxline - 1 && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	if (ch == '\n')
		line[i++] = ch;

	line[i] = '\0';

	return i;
}

void escape(char dest[], char str[])
{
	int i, j;

	for (i = 0, j = 0; str[i] != '\0'; ++i, ++j)
	{
		switch (str[i])
		{
			case '\a':
				dest[j++] = '\\';
				dest[j] = 'a';
				break;

			case '\b':
				dest[j++] = '\\';
				dest[j] = 'b';
				break;

			case '\f':
				dest[j++] = '\\';
				dest[j] = 'f';
				break;

			case '\n':
				dest[j++] = '\\';
				dest[j] = 'n';
				break;

			case '\r':
				dest[j++] = '\\';
				dest[j] = 'r';
				break;

			case '\t':
				dest[j++] = '\\';
				dest[j] = 't';
				break;

			case '\v':
				dest[j++] = '\\';
				dest[j] = 'v';
				break;

			case '\\':
				dest[j++] = '\\';
				dest[j] = '\\';
				break;

			case '?':
				dest[j++] = '\\';
				dest[j] = '?';
				break;

			case '\'':
				dest[j++] = '\\';
				dest[j] = '\'';
				break;

			case '\"':
				dest[j++] = '\\';
				dest[j] = '"';
				break;

			default:
				dest[j] = str[i];
				break;
		}
	}

	if (str[i] == '\0')
		dest[j] = str[i];
}

void unescape(char dest[], char str[])
{
	int i, j;

	for (i = 0, j = 0; str[i] != '\0'; ++i, ++j)
	{
		if (str[i] == '\\')
		{
			switch (str[++i])
			{
				case 'a':
					dest[j] = '\a';
					break;

				case 'b':
					dest[j] = '\b';
					break;

				case 'f':
					dest[j] = '\f';
					break;

				case 'n':
					dest[j] = '\n';
					break;

				case 'r':
					dest[j] = '\r';
					break;

				case 't':
					dest[j] = '\t';
					break;

				case 'v':
					dest[j] = '\v';
					break;

				case '\\':
					dest[j] = '\\';
					break;

				case '?':
					dest[j] = '\?';
					break;

				case '\'':
					dest[j] = '\'';
					break;

				case '"':
					dest[j] = '\"';
					break;

				default:
					dest[j++] = '\\';
					dest[j] = str[i];
			}
		}
		else
			dest[j] = str[i];
	}

	if (str[i] == '\0')
		dest[j] = str[i];
}