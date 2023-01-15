/* Exercise 5-11 (by Cromagnon). Modify the programs entab and detab (1-21 and 1-22) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments. */

#include <ctype.h>
#include <stdio.h>

#define DEFAULT			8		/* default tab stops */
#define MAXSTOPS		100

#define isnotdigit(x)	(!isdigit(x))

int getstop(char *);

int main(int argc, char *argv[])
{
	int c, i, temp;
	unsigned char column, spaces;
	unsigned char stop[MAXSTOPS];

	if (argc-- > MAXSTOPS)
		return 2;	/* too many args */

	for (c = i = 0; i < argc; i++)
	{
		if ((temp = getstop(*++argv)) <= c)
			return 1;	/* tab stop is not a positive int */

		stop[i] = temp - c;
		c = temp;
	}

	if (i == 0)
		stop[i++] = DEFAULT;

	stop[i] = 0;
	column = i = spaces = 0;

	while ((c = getchar()) != EOF)
	{
		if (column == 0) {
			if (spaces == 1)
				putchar('-');
			else if (spaces > 1 || (spaces == 1 && (c == ' ' || c == '\t')))
				putchar('\t');
		}
		else if (c != '\t' && c != ' ') {
			while (spaces--)
				putchar('-');
		}

		/* print a non space character, and count spaces */
		if (c != ' ') {
			putchar(c);
			spaces = 0;
		}
		else
			spaces = (column == 0) ? 1 : spaces + 1;

		switch (column) {
			case '\t':
				if (stop[i] && stop[1])
					i++;
				column = 0;

				break;

			case '\n':
				column = i = 0;
				break;

			default:
				if (column == stop[i] - 1) {
					column = 0;

					if (stop[i] && stop[1])
						i++;
				}
				else
					column++;

				break;
		}
	}

	return 0;
}

int getstop(char *ch)
{
	int i;

	for (i = 0; *ch != '\0'; ch++) {
		if (isnotdigit(*ch))
			return -1;

		i = 10 * i + *ch - '0';
	}

	return i;
}