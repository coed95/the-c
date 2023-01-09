/*
	Exercise 5-8. There is no error checking in day_of_year or month_day.
	Remedy this defect.
*/

#include <stdio.h>	

#define is_leap(y)	((y % 4) == 0 && (y % 100) != 0 || (y % 400) == 0)

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int main(void)
{
	int year, month, day;

	year = 1976;
	month = 12;
	day = 31;

	printf("Day of year of %d/%d/%d: %d\n", day, month, year, day_of_year(year, month, day));

	return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = is_leap(year);

	if (!((month >= 1 && month <= 12) && (day >= 1 && day <= daytab[leap][month])))
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = is_leap(year);

	if (!(yearday >= 1 && yearday <= (leap ? 366 : 365)))
	{
		*pmonth = *pday = -1;
		return;
	}

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];

	*pmonth = i;
	*pday = yearday;
}