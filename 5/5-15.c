/*
	Exercise 5-15. Add the option -f to fold upper and lower case together, so that case distinction are not made during sorting;
	for example, a and A compare equal.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 		1000
#define MAXLINES	5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int order);

void myqsort(void *lineptr[], int left, int right,
		   int (*comp)(void *, void *));

int numcmp(char *, char *);
int strcmp_f(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
	int c, i;
	int nlines;			/* number of input lines read */

	int fold = 0;		/* 1 if upper and lower case letters are folded */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if decreasing order sort */

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		while (c = *++argv[0]) {
			switch (c) {
				case 'f':
					fold = 1;
					break;
				case 'n':
					numeric = 1;
					break;
				case 'r':
					reverse = 1;
					break;
				default:
					printf("Illegal option: -%c\n", c);
					printf("Usage: sort [-f] [-n] [-r]\n");
					argc = 0;
					return EXIT_FAILURE;
			}
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		if (numeric)
			myqsort((void **) lineptr, 0, nlines - 1,
				  (int (*)(void *, void *))(numcmp));
		else if (fold)
			myqsort((void **) lineptr, 0, nlines - 1,
				  (int (*)(void *, void *))(strcmp_f));		/* case insensitive */
		else
			myqsort((void **) lineptr, 0, nlines - 1,
				  (int (*)(void *, void *))(strcmp));		/* case sensitive */

		/* if reverse is true, write lines in decrescent order */
		if (reverse)
			writelines(lineptr, nlines, 1);
		else
			writelines(lineptr, nlines, 0);

		for (i = 0; i < nlines; i++)
			free(lineptr[i]);

		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}

/* get the input line */
int getline(char *line, int max)
{
	int c, i;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == '\n')
		line[i++] = '\n';

	line[i] = '\0';

	return i;
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	int getline(char *line, int max);

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
	{
		lineptr[nlines] = calloc(len, sizeof(char*));

		if ((nlines >= maxlines) || (lineptr[nlines] == NULL))
			return -1;

		line[len - 1] = '\0';	/* delete newline */

		strncpy(lineptr[nlines], line, len);

		if (strcmp(lineptr[nlines], "quit") == 0) {
			printf("Lines: %d\n", nlines);
			return nlines;
		}

		nlines++;
	}

	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int order)
{
	int i;

	/* crescent order */
	if (order == 0) {
		for (i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);
	}
	/* decrescent order */
	else if (order == 1) {
		for (i = nlines - 1; i >= 0; i--)
			printf("%s\n", lineptr[i]);
	}
}

/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(void *v[], int left, int right,
		   int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int i, int j);

	/* return if there are less than 2 elements */
	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}

	swap(v, left, last);
	myqsort(v, left, last - 1, comp);
	myqsort(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = strtod(s1, NULL);
	v2 = strtod(s2, NULL);

	if (v1 < v2)
		return -1;

	if (v1 > v2)
		return 1;

	return 0;
}

/* strcmp_f: compare s1 and s2 (case insensitive) */
int strcmp_f(char *s1, char *s2)
{
    for (; toupper(*s1) == toupper(*s2); s1++, s2++) {
    	if (*s1 == '\0')
        	return 0;
    }

    return toupper(*s1) - toupper(*s2);
}