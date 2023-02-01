/* Exercise 2-8. Write a function rightrot(x, n) that returns the value of the integer x rotated to the right by n bit positions. */

#define INT_BITS	sizeof(int) * 8

unsigned rightrot(unsigned x, int n);

unsigned rightrot(unsigned x, int n)
{
	unsigned bit;

	while (n > 0)
	{
		bit = x & 1;				/* find the least significant bit */
		x >>= 1;					/* right shift the number one time */

		x &= (~(1 << INT_BITS));	/* clear the MSB */
		x |= bit << INT_BITS;		/* set the LSB found as the new MSB */

		--n;
	}

	return x;
}