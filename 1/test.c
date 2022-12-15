#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[256];

	/* should return FF FF FF */
	printf("%x %x %x\n", 255, 255, 255);

	strcpy(str, "hello");
	printf("String: %s\n", str);

	strcpy(str, "world");
	printf("New string: %s\n", str);
	return 0;
}