/*
	Exercise 6-2. Write a program that reads a C program and prints in alphabetical order
	each group of variable names that are identical in the first 6 characters, but different
	somewhere thereafter. Don't count words within strings and comments.
	Make 6 a parameter that can be set from the command line.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE		100
#define MAXWORD		100

#define DEFAULT		6		/* first n characters to compare */
#define MIN(a, b)	(\
	(strlen(a) < strlen(b)) ? strlen(a) : strlen(b))

/* the tree node */
struct tnode {
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

char buf[BUFSIZE];  		/* buffer for ungetch */
int bufp = 0;       		/* next free position in buf */

/* char *strdup(char *); */

int getword(char *, int);
int getch(void);
void ungetch(int);

struct tnode *addtree(struct tnode *, char *, int);
struct tnode *talloc(void);
void tfree(struct tnode *);
void treeprint(struct tnode *);

/* word frequency count */
int main(int argc, char *argv[])
{
	struct tnode *root = NULL;
	char word[MAXWORD];
	int n;

	n = (argc == 1) ? DEFAULT : strtol(argv[1], NULL, 10);

	if (n <= 0) {
		printf("%s is not a valid number\n", argv[1]);
		return 1;
	}

	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word, n - 1);

		if (!strcmp(word, "quit") || !strcmp(word, "exit"))
			break;
	}

	treeprint(root);
	tfree(root);

	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int n)
{
	int cond;

	/* a new word has arrived */
	if (p == NULL)
	{
		p = talloc();			/* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else {
		/* checks the first n characters between w and p->word */
		cond = strncmp(w, p->word, (n <= MIN(w, p->word)) ? n : MIN(w, p->word));

		if (cond == 0) {
			/* repeated word */
			p->count++;
		}
		else if (cond < 0) {
			/* less than into left subtree */
			p->left = addtree(p->left, w, n);
		}
		else {
			/* greater than into right subtree */
			p->right = addtree(p->right, w, n);
		}
	}

	return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* tfree: free a tnode */
void tfree(struct tnode *p)
{
	if (p == NULL)
		return;

	tfree(p->left);
	tfree(p->right);
	free(p);

	if (p->word != NULL)
		free(p->word);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
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
	if (!isalpha(c) && c != '_' && c != '\"' && c != '#' && c != '/') {
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