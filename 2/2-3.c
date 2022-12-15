/* Exercise 2-3. Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NEGATIVE, POSITIVE };

int htoi(char s[]);	/* hex to int */

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stderr, "%s <dec>\n", argv[0]);
		exit(1);
	}

	printf("%s: 0x%d\n", argv[1], itoh(argv[1]));

	return 0;
}

int htoi(char s[])
{
	int i, n;
	int sign;
	int hex;
	int len;

	n = 0;
	i = 0;
	sign = POSITIVE;
	len = strlen(s);

	if (s[i] == '-') {
		sign = NEGATIVE;
		++i;
	}

	if (s[i] == '0')
		++i;

	if (s[i] == 'x' || s[i] == 'X') {
		if (s[i - 1] == '0') {
			++i;
		}
		else {
			return -1;
		}
	}

	for (; i < len; ++i)
	{
		if (s[i] >= '0' && s[i] <= '9') {
			hex = s[i] - '0';
			n = 16 * n + hex;
		}
		else if (s[i] >= 'A' && s[i] <= 'F') {
			hex = s[i] - 'A' + 10;
			n = 16 * n + hex;
		}
		else if (s[i] >= 'a' && s[i] <= 'f') {
			hex = s[i] - 'a' + 10;
			n = 16 * n + hex;
		}
	}

	return (sign == POSITIVE) ? n : (n * -1);
}