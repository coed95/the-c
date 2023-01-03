/* Exercise 5-4. Write the function strend(s, t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise. */

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t)
{
	if (strlen(t) > strlen(s))
		return 0;

	s += strlen(t);

	for (; *s == *t; s++, t++) {
		if (*s == '\0')
			return 1;
	}

	return 0;
}