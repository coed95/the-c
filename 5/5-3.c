/* Exercise 5-3. Write a pointer version of the function strcat(s, t), that copies the string t to the end of s. */

#include <stdio.h>

void pstrcat(char *, char *);

int main(void)
{
	char test[12] = "hello ";
	pstrcat(test, "world");

	printf("%s\n", test);

	return 0;
}

void pstrcat(char *s, char *t)
{
	for (; *s; s++)
		;

	while (*s++ = *t++)
		;
	*s = '\0';
}