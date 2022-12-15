/* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. */

#include <stdio.h>

float conversion(float value);

int main(void)
{
	float fahr;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = (float) lower;

	while (fahr <= upper)
	{
		printf("%3.0f\t\t\t%3.2f\n", fahr, conversion(fahr));
		fahr += step;
	}

	return 0;
}

float conversion(float value)
{
	return (5 * (value - 32)) / 9;
}