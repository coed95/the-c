/* Exercise 1-17. Write a program to print all input lines that are longer than 80 characters.
   But since I'm lazy the new limit will be of 20. */

#include <stdio.h>

#define		MAXCH		20
#define		MAXSTR		100
#define		MAXLINE		1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
	int i, index, len;
	char line[MAXLINE];
	char lines[MAXSTR][MAXLINE];

	index = 0;

	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > MAXCH) {
			copy(lines[index], line);
			++index;
		}
	}

	for (i = 0; i < index; ++i)
		printf("%s", lines[i]);

	return 0;
}

int getline(char line[], int maxline)
{
	int ch, i;

	for (i = 0; i < maxline && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	if (ch == '\n') {
		line[i] = ch;
		++i;
	}

	line[i] = '\0';

	return i;
}

void copy(char to[], char from[])
{
	int i;

	i = 0;

	while (from[i] != '\0')
	{
		to[i] = from[i];
		++i;
	}
}