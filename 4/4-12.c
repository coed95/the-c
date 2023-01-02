/* Exercise 4-12. Adapt the idea of printd to write a recursive function of itoa.
   That is, convert an integer into a string by calling a recursive routine. */

void r_itoa(int n, char s[])
{
	static int i = 0;

	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}

	if (n / 10)
		r_itoa(n / 10, s);

	s[i++] = n % 10 + '0';
	s[i] = '\0';
}