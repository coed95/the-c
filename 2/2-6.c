/* Exercise 2-6. Write a function setbits(x, p, n, y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged. */

unsigned int setbits(int x, int p, int n, int y)
{
	unsigned int mask1, mask2;

	++p;

	mask1 = (~(~(~0 << n) << p) & x);
	mask2 = (~(~0 << n) & y) << p;

	return mask1 | mask2;
}