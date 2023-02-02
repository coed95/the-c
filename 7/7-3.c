/* Exercise 7-3. Revise minprintf to handle more of the other facilities of printf */

#include <stdarg.h>
#include <stdio.h>

void minprintf(char *, ...);

int main(void)
{
	int n = 365;

	minprintf("test\n");
	minprintf("%d %o %x %X\n", n, n, n, n);

	return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	char *p;
	char *sval;
	double dval;
	int cval, ival;
	unsigned int uval;
	va_list ap;		/* points to each unnamed arg in turn */

	/* make ap point to 1st unnamed arg */
	va_start(ap, fmt);

	for (p = fmt; *p != '\0'; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		switch (*++p) {
			case 'c':
				cval = va_arg(ap, int);
				printf("%c", cval);
				break;

			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;

			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;

			case 'o':
				uval = va_arg(ap, unsigned int);
				printf("%o", ival);
				break;

			case 'u':
				uval = va_arg(ap, unsigned int);
				printf("%u", uval);
				break;

			case 's':
				for (sval = va_arg(ap, char *); *sval != '\0'; sval++)
					putchar(*sval);
				break;

			case 'x':
				uval = va_arg(ap, unsigned int);
				printf("%x", uval);
				break;

			case 'X':
				uval = va_arg(ap, unsigned int);
				printf("%X", uval);
				break;

			default:
				putchar(*p);
				break;
		}
	}

	va_end(ap);		/* clean up when done */
}