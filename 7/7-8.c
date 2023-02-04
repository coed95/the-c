/*
	Exercise 7-8. Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE		1000	/* max length of a single line */
#define MAXLINES	10		/* max lines per page */
#define MAXFILES	10		/* max files to read */

struct file {
	FILE *p;
	char *name;
	short pages;
};

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	short i, lines;
	struct file files[MAXFILES];

	if (argc == 1) {
		fprintf(stderr, "Usage: %s [file1] [file2] ...\n", *argv);
		exit(1);
	}

	if ((argc - 1) > MAXFILES) {
		fprintf(stderr, "Error: %s can only read %d files\n", *argv, MAXFILES);
		exit(1);
	}

	for(i = 0, --argc; i < argc; i++) {
		if ((files[i].p = fopen(argv[i + 1], "r")) == NULL) {
			fprintf(stderr, "Error: cannot open file %s\n", argv[i + 1]);
			exit(1);
		}
		files[i].name = argv[i + 1];
		files[i].pages = 0;
	}

	/* set NULL to track the end of files to read */
	files[i].name = NULL;

	for (i = 0, lines = 0; files[i].name != NULL; i++) {
		/* print title */
		printf("\n%s\n", files[i].name);

		/* read the current file */
		while (fgets(line, MAXLINE, files[i].p) != NULL) {
			printf("%s", line);

			if (lines++ >= MAXLINES) {
				/* start a new page */
				printf("Page: %hi\n\n", ++files[i].pages);
				lines = 0;
			}
		}

		/* close the file after reading it */
		fclose(files[i].p);
	}

	return 0;
}