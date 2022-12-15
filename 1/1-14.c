/* Exercise 1-14. Write a program to print a histogram of the frequencies of different characters in its input. */

#include <stdio.h>

#define		ALPHA_LEN		26

int main(void)
{
	int alphabet[ALPHA_LEN];
	int ch, index, j;

	for (index = 0; index < ALPHA_LEN; ++index)
		alphabet[index] = 0;

	while ((ch = getchar()) != EOF)
	{
		if (ch >= 'a' && ch <= 'z')
			++alphabet[ch - 'a'];

		if (ch == '\n')
		{
			for (index = 0; index < ALPHA_LEN; ++index)
			{
				printf("%c: ", index + 'a');

				for (j = 0; j < alphabet[index]; j++)
					putchar('#');

				putchar('\n');
			}

			for (index = 0; index < ALPHA_LEN; index++)
				alphabet[index] = 0;
		}
	}

	return 0;
}