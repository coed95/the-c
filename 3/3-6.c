/*
	Exercise 3-6. Write a version of itoa that accepts three arguments instead of two.
	The third argument is a minimum field width; the converted number must be padded
	with blanks on the left if necessary to make it wide enough.
*/

void itoa(int n, char s[], unsigned int w);

void itoa(int n, char s[], unsigned int w)
{
	int sign, i = 0;

	if ((sign = n) < 0)			/* record sign */
		n = -n;					/* make it positive */

	do {						/* generate digits in reverse order */
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0),	/* delete it */

	if (sign < 0)
		s[i++] = '-';

	while (w > 0) {
		s[i++] = ' ';
		w--;
	}

	reverse(s);
	s[i] = '\0';
}