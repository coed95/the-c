/* Exercise 1-24. Write a program to check a C program for rudimentary syntax errors
   like unbalanced parentheses, brackets and braces. Don't forget about quotes,
   both single and double, escape sequences, and comments.
   (This program is hard if you do it in full generality.) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME  argv[1]

#define SLASH           '/'
#define NEWLINE         '\n'

#define OPEN_ROUND      '('
#define OPEN_SQUARE     '['
#define OPEN_BRACE      '{'

#define CLOSED_ROUND    ')'
#define CLOSED_SQUARE   ']'
#define CLOSED_BRACE    '}'

typedef enum
{
   INCREASE,
   DECREASE
} operation;

void count_brackets(int *brackets, bool comment, operation op);

int main(int argc, char *argv[])
{
   FILE *fp;
   int ch, lines;
   int rounds, squares, braces;
   int slashes;
   bool is_comment;

   if (argc == 1) {
      fprintf(stderr, "%s <file.c>\n", argv[0]);
      exit(1);
   }

   if ((fp = fopen(FILENAME, "r")) == NULL)
   {
      fprintf(stderr, "Couldn't open %s\n", FILENAME);
      exit(1);
   }

   if (strstr(FILENAME, ".c") == NULL) {
      fprintf(stderr, "%s is not a valid file\n", FILENAME);
      exit(1);
   }

   rounds = 0;
   squares = 0;
   braces = 0;
   slashes = 0;

   is_comment = false;

   while ((ch = fgetc(fp)) != EOF)
   {
      switch (ch)
      {
         case SLASH:
            ++slashes;

            if (slashes == 2)
               is_comment = true;

            break;

         case NEWLINE:
            slashes = 0;
            is_comment = false;

            break;

         case OPEN_ROUND:
            count_brackets(&rounds, is_comment, INCREASE);
            break;

         case CLOSED_ROUND:
            count_brackets(&rounds, is_comment, DECREASE);
            break;

         case OPEN_SQUARE:
            count_brackets(&squares, is_comment, INCREASE);
            break;

         case CLOSED_SQUARE:
            count_brackets(&squares, is_comment, DECREASE);
            break;

         case OPEN_BRACE:
            count_brackets(&braces, is_comment, INCREASE);
            break;

         case CLOSED_BRACE:
            count_brackets(&braces, is_comment, DECREASE);
            break;
      }
   }

   /* will make this part better one day */
   if (rounds != 0 || squares != 0 || braces != 0)
      printf("File presents unbalanced parentheses.\n");

   fclose(fp);
   return 0;
}

void count_brackets(int *brackets, bool is_comment, operation op)
{
   if (is_comment == true)
      return;

   if (op == INCREASE)
      *brackets += 1;
   else if (op == DECREASE)
      *brackets -= 1;
}