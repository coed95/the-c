/* Exercise 7-4. Write a private version of scanf analogous to minscanf from the previous section. */

#include <stdarg.h>
#include <stdio.h>

void minscanf(char *, ...);

int main(void)
{
	/* ... */
	return 0;
}

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
	char *p;
	char *sval;
	double *dval;
	int *cval, *ival;
	unsigned int *uval;
	va_list ap;		/* points to each unnamed arg in turn */

	/* make ap point to 1st unnamed arg */
	va_start(ap, fmt);

	for (p = fmt; *p != '\0'; p++) {
		if (*p != '%')
			continue;

		switch (*++p) {
			case 'c':
				cval = va_arg(ap, int *);
				scanf("%c", cval);
				break;

			case 'd':
				ival = va_arg(ap, int *);
				scanf("%d", ival);
				break;

			case 'f':
				dval = va_arg(ap, double *);
				scanf("%f", dval);
				break;

			case 'o':
				uval = va_arg(ap, unsigned int *);
				scanf("%o", ival);
				break;

			case 'u':
				uval = va_arg(ap, unsigned int *);
				scanf("%u", uval);
				break;

			case 's':
				sval = va_arg(ap, char *);
				scanf("%s", sval);
				break;

			case 'x':
				uval = va_arg(ap, unsigned int *);
				scanf("%x", uval);
				break;

			case 'X':
				uval = va_arg(ap, unsigned int *);
				scanf("%X", uval);
				break;

			default:
				putchar(*p);
				break;
		}
	}

	va_end(ap);		/* clean up when done */
}