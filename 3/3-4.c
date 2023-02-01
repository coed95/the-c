/*
 	Exercise 3-4. In a two's complement number representation, our version of itoa doesn't 	handle the largest negative number, that is, the value of n equal to -(2^wordsize-1). 	Explain why not. Modify it to print that value correctly, regardless of the machine on 	which it runs.
*/

/*
 	Explanation:

	if ((sign = n) < 0)
		n = -n;

	doesn't work for the largest negative number because it is one greater compared to the positive one. To make it work, it is possible to do the opposite control: if the sign is positive, make it negative, and then check it back at the end of the do-while loop.
*/

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[])
{
	int sign, i = 0;

	if ((sign = n) > 0)
		n = -n;				/* make it temporarily negative */

	do {
		s[i++] = '0' - (n % 10);
	} while ((n /= 10) < 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}