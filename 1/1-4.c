/* Exercise 1-4. Write a program to print the corresponding Celsius to
   Fahreneit table. */

#include <stdio.h>

int main(void)
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;		/* lower limit */
	upper = 300.0;	/* upper limit */
	step = 20.0;	/* step size */

	celsius = lower;

	printf("Celsius\t\t\tFahreneit\n");

	while (celsius <= upper)
	{
		fahr = celsius * (9.0 / 5.0) + 32.0;
		printf("%6f\t\t%3f\n", celsius, fahr);
		celsius = celsius + step;
	}

	return 0;
}