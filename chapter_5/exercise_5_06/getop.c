#include <stdio.h>
#include <ctype.h>

#define NUMBER 0

int getop(char *s);

int main(void)
{
  char s[100] = "";

  int type = getop(s);

  printf("%d ", type);
  puts(s);

  return 0;
}

int getop(char *s)
{
  char c;

  // Skip blanks (spaces and tabs)
  while ((*s = c = getchar()) != ' ' || c != '\t')
    ;

  *(s + 1) = '\0';

  // Not a number
  if (!isdigit(c) && c != '.')
    return c;

  // Collect the integer part
  if (isdigit(c) && c != '.')
    while (isdigit(*(++s) = c = getchar()))
      ;

  // Collect the fraction part
  if (c == '.')
  {
    while (isdigit(*(++s) = c = getchar()))
      ;
  }

  if (c != EOF)
    ungetc(c, stdin);

  *s = '\0';

  return NUMBER;
}
