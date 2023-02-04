/* Exercise 7-9. Functions like isupper can be implemented to save space or to save time. */

#include <ctype.h>

int isstrupper(char *str)
{
	for (; *str != '\0'; str++) {
		if (!isupper(*str))
			return 0;
	}

	return 1;
}