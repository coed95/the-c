/* Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside). Write a version with only one test inside the loop and measure the difference in run-time. */

#include <time.h>
#include <stdio.h>

#define MAX_ELEMENTS 500000

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main(void)
{
	int v[MAX_ELEMENTS];
	int i, j, x;
	clock_t t;

	for (i = 0; i < MAX_ELEMENTS; ++i)
		v[i] = i;

	j = -1;	/* value to find */

	/* time taken for 500000 iterations of binsearch */

	t = clock();
	for (i = 0; i < MAX_ELEMENTS; ++i)
		x = binsearch(j, v, MAX_ELEMENTS);

	printf("Current time: %d\n", t);
	t = clock() - t;

	if (j < 0)
		printf("Element %d not found.\n", j);
	else
		printf("Element %d found at position %d.\n", j, x);

	printf("binsearch() took %lu seconds to execute.\n",
		  (unsigned long) t / CLOCKS_PER_SEC);

	/* time taken for 500000 iteration of binsearch2 */

	t = clock();
	for (i = 0; i < MAX_ELEMENTS; ++i)
		x = binsearch2(j, v, MAX_ELEMENTS);

	printf("Current time: %d\n", t);
	t = clock() - t;

	if (j < 0)
		printf("Element %d not found.\n", j);
	else
		printf("Element %d found at position %d.\n", j, x);

	printf("binsearch2() took %lu seconds to execute.\n",
		  (unsigned long) t / CLOCKS_PER_SEC);

	return 0;
}

int binsearch(int x, int v[], int n)
{
	int low, mid, high;

	low = 0;
	high = n - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

int binsearch2(int x, int v[], int n)
{
	int low, mid, high;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;

	while (low <= high && x != v[mid])
	{
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;

		mid = (low + high) / 2;
	}

	return (x == v[mid]) ? mid : -1;
}