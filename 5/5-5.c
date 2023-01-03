/* Exercise 5-5. Write versions of the library functions strncpy, strncat and strncmp. */

#include <stddef.h>

void pstrncpy(char *, char *, size_t);
void pstrncat(char *, char *, size_t);
int pstrncmp(char *, char *, size_t);

void pstrncpy(char *s, char *t, size_t n)
{
	while ((*s++ = *t++) && (n-- > 0))
		;
	*s = '\0';
}

void pstrncat(char *s, char *t, size_t n)
{
	for (; *s; s++)
		;

	while (*t && n-- > 0)
		*s++ = *t++;

	*s = '\0';
}

int pstrncmp(char *s, char *t, size_t n)
{
	int i;

    for (i = 0; i < n && *(s + i) == *(t + i) && *(s + i); i++)
		;

    return (unsigned char)*(s + i) - (unsigned char)*(t + i);
}