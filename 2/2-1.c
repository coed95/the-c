/* Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating point types. */

#include <stdio.h>
#include <limits.h>

#define N_TYPES			19

float getfloat(char sign, unsigned char exp, unsigned mantissa);
double getdouble(char sign, unsigned short exp, unsigned long long mantissa);

int main(void)
{
	int index;
	char type_name[N_TYPES][12] = {
		"CHAR_BIT",
		"SCHAR_MIN",
		"SCHAR_MAX",
		"UCHAR_MAX",
		"CHAR_MIN",
		"CHAR_MAX",
		"MB_LEN_MAX",
		"SHRT_MIN",
		"SHRT_MAX",
		"USHRT_MAX",
		"INT_MIN",
		"INT_MAX",
		"UINT_MAX",
		"LONG_MIN",
		"LONG_MAX",
		"ULONG_MAX",
		"LLONG_MIN",
		"LLONG_MAX",
		"ULLONG_MAX"};

	long long type_value[] = {
		CHAR_BIT,
		SCHAR_MIN,
		SCHAR_MAX,
		UCHAR_MAX,
		CHAR_MIN,
		CHAR_MAX,
		MB_LEN_MAX,
		SHRT_MIN,
		SHRT_MAX,
		USHRT_MAX,
		INT_MIN,
		INT_MAX,
		UINT_MAX,
		LONG_MIN,
		LONG_MAX,
		ULONG_MAX,
		LLONG_MIN,
		LLONG_MAX,
		ULLONG_MAX};

	for (index = 0; index < N_TYPES; ++index) {
		if (type_value[index] == ULLONG_MAX)
			printf("%s: %llu\n", type_name[index], type_value[index]);
		else
			printf("%s: %lli\n", type_name[index], type_value[index]);
	}

	putchar('\n');
	printf("FLOAT: %g to %g\n", getfloat(1, 0, 1), getfloat(0, ~0 - 1, ~0));
	printf("DOUBLE: %g to %g\n", getdouble(1, 0, 1), getdouble(0, ~0 - 1, ~0));

	return 0;
}

float getfloat(char sign, unsigned char exp, unsigned mantissa)
{
	unsigned f;

	f = (unsigned) (sign != 0) << 31 | (unsigned) exp << 23 | mantissa & 0x7FFFFF;

	return *((float *) &f);
}

double getdouble(char sign, unsigned short exp, unsigned long long mantissa)
{
	unsigned long long d;

	d = (unsigned long long) (sign != 0) << 63 | (unsigned long long) (exp & 0x7FF) << 52 | mantissa & 0xFFFFFFFFFFFFF;

	return *((double *) &d);
}