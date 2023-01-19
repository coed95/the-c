#include <stdio.h>
#include <string.h>

#include "dcl.h"

/* convert declaration to word */
int main(void)
{
	while (gettoken() != EOF) {
		/* first token on line is the datatype */
		strncpy(datatype, token, MAXTOKEN);
		out[0] = '\0';

		/* parse the rest of the line */
		dcl();

		if (tokentype != '\n')
			printf("syntax error\n");

		printf("%s: %s %s\n", name, out, datatype);
	}

	return 0;
}