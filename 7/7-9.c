/* Exercise 7-9. Functions like isupper can be implemented to save space or to save time. */

#include <stdio.h>

#define isupper(x)	(x >= 'A' && x <= 'Z')

int isstrupper(char *);

int main(int argc, char *argv[])
{
	char *str = (argc == 1) ? "DEFAULT" : argv[1];

	if (isstrupper(str))
		printf("%s is upper\n", str);
	else
		printf("%s is not upper\n", str);

	return 0;
}

int isstrupper(char *str)
{
	for (; *str != '\0'; str++) {
		if (!isupper(*str))
			return 0;
	}

	return 1;
}