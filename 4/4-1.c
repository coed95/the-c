/* Exercise 4-1. Write the function strrindex(s, t), which returns the position of the rightmost occurrence of t in s, or -1 if there is none. */

#include <stdio.h>
#include <string.h>

int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);

int main(void)
{
	char str[] = "hello world";
	char needle[] = "l";

	printf("str: %s\n", str);
	printf("position of the leftmost %s: %d\n", needle, strindex(str, needle));
	printf("position of the rightmost %s: %d\n", needle, strrindex(str, needle));

	return 0;
}

/* return index of t in s, -1 if none */
int strindex(char source[], char searchfor[])
{
	int i, j, k;

	for (i = 0; source[i] != '\0'; i++) {
		for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
			;

		if (k > 0 && searchfor[k] == '\0')
			return i;
	}

	return -1;
}

/* return index of the rightmost t in s, -1 if none */
int strrindex(char source[], char searchfor[])
{
	int i, j, k;

	for (i = strlen(source) - 1; i >= 0; i--) {
		for (j = i, k = strlen(searchfor) - 1; k >= 0 && source[j] == searchfor[k]; j--, k--)
			;

		if (k < 0)
			return i - (strlen(searchfor) - 1);
	}

	return -1;
}