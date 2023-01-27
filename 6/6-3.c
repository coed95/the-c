/*
	Exercise 6-3.
	Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs.
	Remove noise words like "the", "and", and so on.
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
	int *lines;				/* lines where the word occurs */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

char buf[BUFSIZE];  		/* buffer for ungetch */
int bufp = 0;       		/* next free position in buf */

int getword(char *, int, int *);

struct tnode *addtree(struct tnode *, char *, int);
void tfree(struct tnode *);
void treeprint(struct tnode *);

/* word frequency count */
int main(int argc, char *argv[])
{
	struct tnode *root = NULL;
	char word[MAXWORD];
	int nlines = 0;		/* number of lines read */

	while (getword(word, MAXWORD, &nlines) != EOF)
	{
		/* if there is a word and it's not a noise */
		if (isalpha(word[0]) && IS_NOT_NOISE_WORD(word) && strcmp(word, "quit") != 0 && strcmp(word, "exit") != 0 && strcmp(word, "q") != 0)
			root = addtree(root, word, nlines);

		if (!strcmp(word, "quit") || !strcmp(word, "exit") || word[0] == 'q')
			break;
	}

	treeprint(root);
	tfree(root);

	return 0;
}

/* addtree: add a node with the word w at line l, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int l)
{
	int cond;

	/* a new word has arrived */
	if (p == NULL)
	{
		/* make a new node */
		p = malloc(sizeof(struct tnode));
		p->word = strdup(w);
		p->count = 1;
		p->lines = calloc(p->count + 1, sizeof(int));
		p->lines[p->count - 1] = l;
		p->left = p->right = NULL;
	}
	else {
		cond = strcmp(w, p->word);

		if (cond == 0) {
			/* repeated word */
			p->count++;
			p->lines = realloc(p->lines, (p->count + 1) * sizeof(int));
			p->lines[p->count - 1] = l;
		}
		else if (cond < 0) {
			/* less than into left subtree */
			p->left = addtree(p->left, w, l);
		}
		else {
			/* greater than into right subtree */
			p->right = addtree(p->right, w, l);
		}
	}

	return p;
}

/* tfree: free a tnode */
void tfree(struct tnode *p)
{
	if (p == NULL)
		return;

	tfree(p->left);
	tfree(p->right);

	if (p->word != NULL) {
		free(p->word);
		p->word = NULL;
	}

	if (p->lines != NULL) {
		free(p->lines);
		p->lines = NULL;
	}

	free(p);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	int i;

	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s: [%d", p->count, p->word, p->lines[0]);

		for (i = 1; i < p->count; i++)
			printf(", %d", p->lines[i]);

		printf("]\n");
		treeprint(p->right);
	}
}

/* getword: get next word or character from input */
int getword(char *word, int lim, int *nlines)
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

		if (c == '\n')
			(*nlines)++;

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