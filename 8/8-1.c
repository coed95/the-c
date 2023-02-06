/*
	Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open and close instead of their standard library equivalent.
	Perform experiments to determine the relative speeds of the two versions.
*/

#include <io.h>
#include <stdio.h>

#ifndef O_RDONLY
#define O_RDONLY	00
#endif

/* cat: concatenate file */
int main(int argc, char *argv[])
{
	int fd;
	void filecopy(int, int);

	if (argc == 1)
		filecopy(0, 1);
	else {
		if ((fd = open(*++argv, O_RDONLY, 0)) < 0) {
			fprintf(stderr, "cat: cannot open %s\n", *argv);
			return 1;
		}
		else {
			filecopy(fd, 1);
			close(fd);
		}
	}

	return 0;
}

void filecopy(int ifd, int ofd)
{
	int c;

	while (read(ifd, &c, 1) > 0)
		write(ofd, &c, 1);
}