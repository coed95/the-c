/* Exercise 2-4. Write an alternate version of squeeze(s1, s2) that deletes each character in s1 that matches any character in the string s2. */

// Hello world
//  e  o

#include <stdio.h>

void squeeze(char s[], int c);
void strsqueeze(char s1[], char s2[]);

int main(void)
{
	return 0;
}

void squeeze(char s, int c)
{
	int i, j;

	for (i = 0, j = 0; s[i] != '\0'; ++i)
	{
		if (s[i] == c)
			s[j++] = s[i];
	}

	s[j] = '\0';
}