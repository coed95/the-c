/*
	Exercise 5-17 (by anonymous). Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000 // max #lines to be sorted
#define MAXLEN 1000 // max length of any input line
#define ALLOCSIZE 10000 // size of available space

char *lineptr[MAXLINES]; // pointers to text lines
static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free position

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int, int);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
int getline(char *s, int lim);
char *alloc(int n);
void myqsort(void *lineptr[], int left, int right, int (*comp)(void *, void *)); // qsort had to be renamed to myqsort since stdlib.h is included.
int reverseCompare(void *, void *); // used to call baseCompare with the arguments in reverse order
int numcmp(const char *, const char *);
int dircmp(const char *, const char *);
char *getField(char *, char *, int);


enum booelan { FALSE, TRUE }; // FALSE == 0, TRUE == 1, this creates booleans in a language that that doesn't natively support them unless you import stdbool.h in c99 or newer

int (*baseCompare)(void *, void *); // function pointer called baseCompare which points to either numcmp or cmpstr depending on the sorting type
int (*compare)(void *, void *); // function pointer called compare that will either point to the regular compare function baseCompare, or a new function called reverseCompare
int caseInsensitive = FALSE, field = 0;
char a[MAXLEN], b[MAXLEN]; // used for getField

// sort input lines
int main(int argc, char *argv[])
{   // nlines = number of input lines read, numeric, reverse, and dirOrder are flags for features turned on in the arguments
    int nlines, numeric, reverse, dirOrder, lexicographic;

    if ((nlines = readlines(lineptr, MAXLINES)) < 0)
    {
        printf("input too big to sort\n");
        return 1;
    }

    while (--argc > 0 && **++argv == '-') // checks the first char in each argument starting at argv[1]
    {
        field = 0;
        numeric = reverse = caseInsensitive = dirOrder = lexicographic = FALSE;
        while (*++*argv)
            if (field != 0)
                break;
            else
                switch (**argv)
                {
                case 'n':
                    numeric = TRUE;
                    break;
                case 'r':
                    reverse = TRUE;
                    break;
                case 'f':
                    caseInsensitive = TRUE;
                    break;
                case 'd':
                    dirOrder = TRUE;
                    break;
                case 'l':
                    lexicographic = TRUE;
                    break;
                default:
                    if (isdigit(**argv) && !(numeric || reverse || caseInsensitive || dirOrder || lexicographic)) // found -#
                    {
                        argc = -1; // triggers usage message
                        break;
                    }
                    else if (isdigit(**argv))
                        field = atoi(*argv);
                    else
                        argc = -1; // triggers usage message
                    break;
                }

        if (field < 0)
        {
            printf("Error: field choices must be positive ints\n");
            return 1;
        }

        baseCompare = (int (*)(void *, void *))(lexicographic ? strcmp : numeric ? numcmp : dirOrder ? dircmp : caseInsensitive ? strcmpi : strcmp); // chooses comparison function based on flags
        myqsort((void **) lineptr, 0, nlines - 1, reverse ? reverseCompare : baseCompare);
    }

    if (argc != 0)
    {
        printf("Usage: sort [-n[#]] [-r[#]] [-f[#]] [-d[#]] [-l[#]]\n");
        return 1;
    }

    writelines(lineptr, nlines);
    return 0;
}

// sort v[left]...v[right] into increasing order
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right) // do nothing if array contains fewer than two elements
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(getField(v[i], a, field), getField(v[left], b, field)) < 0)
            swap(v, ++last, i);
        
    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

// compare s1 and s2 numerically
int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    return 0;
}

// swaps int i and j
void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0'; // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

// write output lines
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

// get line into s, return length
int getline(char *s, int lim)
{
    int c;
    char *original = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - original; // returns length
}

// return pointer to n characters
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) // it fits
    {
        allocp += n; // update marker to note where the next unallocated memory starts
        return allocp - n; // old pointer address
    }
    else
        return 0; // not enough room
}

int reverseCompare(void *left, void *right)
{
    return (*baseCompare)(right, left); // reverses the order that items are compared and which causes it to be sorted in reverse (descending) order
}

// compare s1 and s2 via directory order (compares only on letters, numbers, and blanks)
int dircmp(const char *s1, const char *s2)
{
    int i = 0, j = 0;
    while (s1[i] || s2[i])
        if (isalnum(s1[i]) || isspace(s1[i]))
            if (isalnum(s2[j]) || isspace(s2[j]))
                if (caseInsensitive ? tolower(s1[i]) < tolower(s2[j]) : s1[i] < s2[j])
                    return -1;
                else if (caseInsensitive ? tolower(s1[i]) > tolower(s2[j]) : s1[i] > s2[j])
                    return 1;
                else
                    i++, j++;
            else
                j++;
        else
            i++;

    return 0;
}

// assumes that fields are tab delimited. Searches s for the nth field and returns it in t. If invalid n or field doesn't exist, returns s
char *getField(char *s, char *t, int n)
{
    if (n <= 0) // invalid n
        return s;
    int i = 0, j = 0;
    while (TRUE)
        if (s[i] == '\t' || s[i] == '\n' || s[i] == '\0') // last field ends with a '\n' or '\0'
            if (--n == 0) // if n == 0, field found
            {
                t[j] = '\0'; // field found! terminate string and return it
                return t;
            }
            else if (s[i] == '\0') // reach end of string
                break;
            else
            {
                j = 0; // reset j so t starts new string for new field
                s++; // move to next char for s
            }
        else
            t[j++] = s[i++]; // copy chars until tab is found
    
    return s; // if field doesn't exist, return s
}