/* for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
   Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||. */

#include <stdio.h>

#define MAXLINE		1024

int getline(char line[], int maxline);

int main(void)
{
	char line[MAXLINE];

	while (getline(line, MAXLINE) > 0)
		printf("%s", line);

	return 0;
}

int getline(char line[], int maxline)
{
	int i, c;

	for (i = 0; i < maxline - 1; ++i)
	{
		c = getchar();

		if (c == '\n') {
			line[i] = c;
			++i;

			break;
		}

		if (c == EOF) {
			return 0;
		}

		line[i] = c;
	}

	line[i] = '\0';

	return i;
}