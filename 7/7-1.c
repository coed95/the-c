/*
	Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0].
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum conversion {
	TO_LOWER,
	TO_UPPER
};

int main(int argc, char *argv[])
{
	enum conversion type;
	int c;

	if (argc != 2) {
		printf("Usage: %s [-l] [-U]\n", argv[0]);
		return 1;
	}

	if (!strcmp(argv[1], "-l"))
		type = TO_LOWER;
	else if (!strcmp(argv[1], "-U"))
		type = TO_UPPER;
	else {
		printf("Error: invalid argument %s\n", argv[1]);
		return 1;
	}

	while ((c = getchar()) != EOF)
	{
		if (type == TO_LOWER)
			putchar(tolower(c));
		else if (type == TO_UPPER)
			putchar(toupper(c));
	}

	return 0;
}