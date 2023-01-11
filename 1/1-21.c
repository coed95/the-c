/* Exercise 1-21. Write a program "entab" which replaces strings of blanks with the minimum number of tabs and blanks to achieve the same spacing. */

#include <stdio.h>

#define	MAXLINE		1000
#define	TAB_LEN		4

char line[MAXLINE];

int getline(void);

int main(void)
{
	int i, j;
	int len, spaces;

	while ((len = getline()) > 0) {
		spaces = 0;

		for (i = 0; i < len; i++) {
			if (line[i] == ' ')
				spaces++;
			if (line[i] != ' ')
				spaces = 0;	/* reset counter */
			if (spaces == TAB_LEN) {
				/* remove 4 spaces, which means remove 3 spaces and add '\t' at start */
				i -= 3;
				len -= 3;
				line[i] = '\t';

				/* move all chars to the right */
				for (j = i + 1; j < len; j++)
					line[j] = line[j + 3];

				spaces = 0;
				line[len] = '\0';
			}
		}

		printf("%s", line);
	}
	
	return 0;
}

int getline(void)
{
	int ch, i;
	extern char line[];

	for (i = 0; i < MAXLINE - 1 && (ch = getchar()) != EOF && ch != '\n'; ++i)
		line[i] = ch;

	if (ch == '\n')
		line[i++] = ch;

	line[i] = '\0';

	return i;
}