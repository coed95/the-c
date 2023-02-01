/* Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else. */

void lower(char str[])
{
	int i;

	for (i = 0; str[i] != '\0'; ++i)
		str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
}