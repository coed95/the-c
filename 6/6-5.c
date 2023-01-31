/*
	Exercise 6-5. Write a function undef that will remove a name and definition from the table maintainted by lookup and install.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	HASHSIZE	101

/* table entry */
struct nlist
{
	struct nlist *next;		/* next entry in chain */
	char *name;				/* defined name */
	char *defn;				/* replacement text */
};

struct nlist *install(char *, char *);
struct nlist *lookup (char *);
unsigned hash(char *);
void undef(char *);

/* pointer table */
static struct nlist *hashtab[HASHSIZE];

int main(void)
{
	int i;

	for (i = 0; i < HASHSIZE; i++)
		hashtab[i] = NULL;

	install("IN", "1");

	if (lookup("IN"))
		printf("IN is in the table (1)\n");
	else
		printf("IN is not in the table (1)\n");

	undef("IN");

	if (lookup("IN"))
		printf("IN is in the table (2)\n");
	else
		printf("IN is not in the table (2)\n");

	return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np = hashtab[hash(s)];

	for (; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0)
			/* found */
			return np;
	}
	/* not found */
	return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	/* not found */
	if ((np = lookup(name)) == NULL)
	{
		np = malloc(sizeof(*np));
		np->name = strdup(name);

		if (np == NULL || np->name == NULL)
			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	/* already there */
	else
		free(np->defn);		/* free previous defn */

	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

	return np;
}

/* undef: remove a name from the table */
void undef(char *name)
{
	struct nlist *np1, *np2;
	unsigned hashval = hash(name);

	if ((np1 = lookup(name)) == NULL)
		return;

	for (np1 = np2 = hashtab[hashval]; np1 != NULL; np2 = np1, np1 = np1->next)
	{
		/* if the name is found */
		if (!strcmp(np1->name, name)) {
			if (np1 == np2)
				hashtab[hashval] = np1->next;
			else
				np2->next = np1->next;

			/* remove it */
			free(np1->name);
			free(np1->defn);
			free(np1);

			return;
		}
	}
}