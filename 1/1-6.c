/* Exercise 1-6. Verify that the expression getchar() != EOF is 0 or 1. */

#include <stdio.h>

int main(void)
{
	/* any character different from EOF will produce 1, otherwise 0 */
	printf("%d\n", getchar() != EOF);
	return 0;
}