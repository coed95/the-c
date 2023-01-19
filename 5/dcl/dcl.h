#ifndef DCL_H
#define DCL_H

#define BUFSIZE		100
#define	MAXTOKEN	100
#define MAXOUTPUT	1000

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);

extern int tokentype;					/* type of last token */
extern char token[MAXTOKEN];			/* last token string */
extern char name[MAXTOKEN];				/* identifier name */
extern char datatype[MAXTOKEN];			/* data type = char, int, etc. */
extern char out[MAXOUTPUT];				/* output string */

extern char buf[BUFSIZE];				/* buffer for ungetch */
extern int bufp;						/* next free position in buf */

#endif