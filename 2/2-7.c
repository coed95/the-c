/* Exercise 2-7. Write a function invert(x, p, n) that returns x with the n bits that begin at position p inverted, leaving the others unchanged. */

unsigned invert(unsigned num, int start, int end);

unsigned invert(unsigned num, int start, int end)
{
	while (start >= end)
	{
		/* if bit is 1 */
		if ((num >> start) & 1)
			num &= ~(1 << start);	/* unset it */
		else
			num |= (1 << start);	/* set it */

		--start;
	}

	return num;
}