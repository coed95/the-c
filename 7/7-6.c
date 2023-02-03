/*
	Exercise 7-6. Write a program to compare two files, printing the first line where they differ.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE		1000

void open_error(char *);

int main(int argc, char *argv[])
{
	char line1[MAXLINE], line2[MAXLINE];
	FILE *fp1, *fp2;
	int n_line;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename1 [filename2]\n", *argv);
		exit(1);
	}

	fp1 = fopen(argv[1], "r");
	fp2 = (argc < 3) ? stdin : fopen(argv[2], "r");

	if (fp1 == NULL)
		open_error(argv[1]);

	if (fp2 == NULL)
		open_error(argv[2]);

	n_line = 0;
	while (fgets(line1, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL)
	{
		n_line++;

		/* if lines are different */
		if (strcmp(line1, line2)) {
			/* print the line where they differ */
			printf("%d %s\n", n_line, line1);
			printf("%d %s\n", n_line, line2);
			break;
		}
	}

	fclose(fp1);

	if (fp2 != stdin)
		fclose(fp2);

	return 0;
}

/* open_error: returns an error if file is not accessible */
void open_error(char *filename)
{
	fprintf(stderr, "Error: could not open %s\n", filename);
	exit(1);
}