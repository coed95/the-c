/* Exercise 1-3. Modify the temperature conversion program to print a heading
   above the table. */

#include <stdio.h>

int main(void)
{
	int fahr, celsius;
	int lower, upper, step;

	lower = 0;		/* lower limit */
	upper = 300;	/* upper limit */
	step = 20;		/* step size */

	fahr = lower;

	printf("Fahreneit\tCelsius\n");

	while (fahr <= upper)
	{
		celsius = 5 * (fahr - 32) / 9;
		printf("%3d\t\t%6d\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;
}