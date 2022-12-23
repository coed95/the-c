/* Exercise 3-3. Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc..xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally. */

#include <ctype.h>
#include <stdio.h>

#define MAXLINE 1024

#define is_alpha_or_digit(x)	(isalpha(x) || isdigit(x))

void expand(char s1[], char s2[]);

int main(void)
{
	char str1[] = "helloa-a-b-world";
	char str2[MAXLINE];

	expand(str1, str2);
	printf("%s\n", str2);

	return 0;
}

void expand(char s1[], char s2[])
{
	int ch;
	int i, j;

	for (i = 0, j = 0; s1[i] != '\0'; i++)
	{
		/* take all chars that are not digits or letters, and also
		   all leading or trailing '-' */
		if (!is_alpha_or_digit(s1[i]) && s1[i] != '-') {
			s2[j++] = s1[i];
		}
		else if (is_alpha_or_digit(s1[i])) {
			if (s1[i + 1] != '-') {
				s2[j++] = s1[i];
			}
			else if (s1[i + 1] == '-' && is_alpha_or_digit(s1[i + 2]))
			{
				/* expands the shorthand notations both in crescent and decrescent order */
				if (s1[i] < s1[i + 2]) {
					for (ch = s1[i]; ch < s1[i + 2]; ch++) {
						s2[j++] = ch;
					}
				}
				else {
					for (ch = s1[i]; ch > s1[i + 2]; ch--) {
						s2[j++] = ch;
					}
				}
			}
		}
	}

	s2[j] = '\0';
}