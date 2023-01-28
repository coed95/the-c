/*
	Exercise 6-4.
	Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE		100
#define MAXWORD		100

#define IS_NOISE_WORD(word) \
    (strcmp(word, "a") == 0 || \
    strcmp(word, "an") == 0 || \
    strcmp(word, "the") == 0 || \
    strcmp(word, "and") == 0 || \
    strcmp(word, "or") == 0 || \
    strcmp(word, "of") == 0 || \
    strcmp(word, "to") == 0 || \
    strcmp(word, "are") == 0 || \
    strcmp(word, "was") == 0 || \
    strcmp(word, "were") == 0 || \
    strcmp(word, "be") == 0 || \
    strcmp(word, "been") == 0 || \
    strcmp(word, "being") == 0 || \
    strcmp(word, "have") == 0 || \
    strcmp(word, "has") == 0 || \
    strcmp(word, "had") == 0 || \
    strcmp(word, "having") == 0 || \
    strcmp(word, "i") == 0 || \
    strcmp(word, "in") == 0 || \
    strcmp(word, "is") == 0 || \
    strcmp(word, "it") == 0)
    /* etc. */

#define IS_NOT_NOISE_WORD(word)	(!IS_NOISE_WORD(word))

/* the tree node */
struct tnode {
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *next;		/* next word */
};

char buf[BUFSIZE];  		/* buffer for ungetch */
int bufp = 0;       		/* next free position in buf */

int getword(char *, int);
int numcmp(int, int);

struct tnode *addtree(struct tnode *, char *);
void tfree(struct tnode *);
void treeprint(struct tnode *);

/* word frequency count */
int main(int argc, char *argv[])
{
	struct tnode *root = NULL;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
	{
		/* if there is a word and it's not a noise */
		if (isalpha(word[0]) && IS_NOT_NOISE_WORD(word) && strcmp(word, "quit") != 0 && strcmp(word, "exit") != 0 && strcmp(word, "q") != 0)
			root = addtree(root, word);

		if (!strcmp(word, "quit") || !strcmp(word, "exit") || word[0] == 'q')
			break;
	}

	treeprint(root);
	tfree(root);

	return 0;
}

/* addtree: add a node with the word w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	void swap(void *, void *, int);

	/* a new word has arrived */
	if (p == NULL)
	{
		/* make a new node */
		p = malloc(sizeof(struct tnode));
		p->word = strdup(w);
		p->count = 1;
		p->next = NULL;
	}
	else {
		cond = strcmp(w, p->word);

		if (cond == 0) {
			/* repeated word */
			p->count++;
		}
		else {
			/* next word */
			p->next = addtree(p->next, w);

			/* if next word has more occurrence than the previous one */
			if (p->next->count > p->count) {
				/* swap the next node with the previous one */
				swap(&p->count, &p->next->count, sizeof(int));
				swap(&p->word, &p->next->word, sizeof(char*));
			}
		}
	}

	return p;
}

/* tfree: free a tnode */
void tfree(struct tnode *p)
{
	if (p == NULL)
		return;

	tfree(p->next);

	if (p->word != NULL) {
		free(p->word);
		p->word = NULL;
	}

	free(p);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	int i;

	if (p != NULL) {
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->next);
	}
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	char *w = word;
	int c, getch(void);
	void ungetch(int);

	int in_comment = 0;		/* 1 if inside a comment */
	int in_pp_line = 0;		/* 1 if inside a preprocessor line */
	int in_string = 0;		/* 1 if inside a string */

	/* skip spaces */
	while (isspace(c = getch()))
		;

	if (c != EOF)
		*w++ = c;

	/* not underscore, pp line, comment, string */
	if (!isalpha(c) && c != '_' && c != '\"' && c != '#' && c != '/' && c != '\n') {
		*w = '\0';
		return c;
	}

	if (c == '\"')
		in_string = 1;

	if (c == '#')
		in_pp_line = 1;

	/* it only checks single line comments for now */
	if (c == '/') {
		if ((c = getch()) == '/')
			in_comment = 1;
		else
			ungetch(c);
	}

	while (--lim > 0)
	{
		c = getch();

		if (in_comment && (c == '\n'))
			in_comment = 0;

		if (in_pp_line && (c == '\n'))
			in_pp_line = 0;

		/* if the char is in a string or in a comment or in a pp line, and is not alphanumeric */
		if (!isalnum(c) && c != '_' && (in_string == 1 || c != '\"') && !in_pp_line && !in_comment)
		{
			ungetch(c);
			break;
		}

		if (c == '/' && *(w - 1) == '/')
			in_comment = 1;

		if (c == '\"')
			in_string = (in_string == 1) ? 0 : 1;

		*w++ = c;
	}

	*w = '\0';

	return word[0];
}

/* numcmp: compare n1 and n2 */
int numcmp(int n1, int n2)
{
	if (n1 < n2)
		return -1;
	if (n1 > n2)
		return 1;

	return 0;
}

/* get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* swap two values */
void swap(void *a, void *b, int size)
{
	char *aa = a;
	char *bb = b;
	char t;
	int i;

	for (i = 0; i < size; i++) {
		t = aa[i];
		aa[i] = bb[i];
		bb[i] = t;
	}
}