/* Exercise 2-5. Write the function any(s1, s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. */

#include <stdio.h>

int find(char str[], int ch);
int any(char s1[], char s2[]);

int main(void)
{
	char str1[] = "abcde2fghi3jk4l";
	char str2[] = "zv";
	int ret;

	printf("String to analyze: %s\n", str1);
	ret = any(str1, str2);
	printf("First matching character of %s at position %d\n", str2, ret);

	return 0;
}

int find(char str[], int ch)
{
	int i;

	for (i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == ch)
			return i;
	}

	return -1;
}

int any(char s1[], char s2[])
{
	int index;

	for (; *s2 != '\0'; s2++) {
		index = find(s1, *s2);

		if (index != -1)
			return index;
	}

	return -1;
}