/* Exercise 1-19. Write a function reverse(s) that reverses the character string s.
   Use it to write a program that reverses its input a line at a time. */

#include <stdio.h>

#define 	MAXLINE		1000

int getline(char line[], int maxline);
void reverse(char str[]);

int main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0)
	{
		reverse(line);
		printf("%s", line);
	}

	return 0;
}

int getline(char line[], int maxline)
{
	int i, ch;

	for (i = 0; i < maxline && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	if (ch == '\n') {
		line[i] = ch;
		++i;
	}

	line[i] = '\0';

	return i;
}

void reverse(char str[])
{
	int i, j, len;
	char temp;

	for (len = 0; str[len] != '\0'; ++len)
		;	

	/* length minus '\0' and '\n' */
	for (i = 0, j = len - 2; j > i; ++i, --j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}

}