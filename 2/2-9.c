/* Exercise 2-9. In a 2's complement number system, x &= (x - 1) deletes the rightmost 1 bit in x. Explain why. Use this observation to write a faster version of bitcount. */

/* & performs an AND bitwise; x and (x - 1) will always have a different bit between them, therefore this operation clears the LSB every time. */

int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x &= (x - 1))
		++b;

	return b;
}