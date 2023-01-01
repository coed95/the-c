/* Exercise 4-13. Write a recursive version of reverse(s). */

#include <stdio.h>
#include <string.h>

void reverse(char []);
void rreverse(char [], int, int);

int main(void)
{
	char str1[] = "hello world";
	char str2[] = "hello world";

	reverse(str1);
	printf("%s\n", str1);

	rreverse(str2, 0, strlen(str2) - 1);
	printf("%s\n", str2);

	return 0;
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void rreverse(char s[], int left, int right)
{
	int temp;

	temp = s[left];
	s[left] = s[right];
	s[right] = temp;

	if (left < right)
		rreverse(s, left + 1, right - 1);
}