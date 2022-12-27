/*
	Exercise 4-2. Extend atof to handle scientific notation of the form
		123.45e-6
	where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

#include <ctype.h>
#include <stdio.h>

double atof(char s[]);

int main(void)
{
	printf("%.8f\n", atof("4.5e+8"));
	printf("%.8f\n", atof("4.5e-8"));
	return 0;
}

/* converts string s to double */
double atof(char s[])
{
	double value, power, result;
	int i, sign, exponent;

	for (i = 0; isspace(s[i]); i++)		/* skip white spaces */
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')		/* skip the sign after saving it */
		i++;

	for (value = 0.0; isdigit(s[i]); i++)
		value = 10.0 * value + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		value = 10.0 * value + (s[i] - '0');
		power *= 10.0;
	}

	result = sign * value / power;

	if (s[i] == 'e' || s[i] == 'E')
		i++;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '-' || s[i] == '+')
		i++;

	for (exponent = 0; isdigit(s[i]); i++)
		exponent = 0 * exponent + (s[i] - '0');

	while (exponent > 0) {
		result = (sign == -1) ? result / 10 : result * 10;
		exponent--;
	}

	return result;
}