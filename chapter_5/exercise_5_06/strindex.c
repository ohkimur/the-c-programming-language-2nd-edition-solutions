#include <stdio.h>

int strindex(char *s, char *t);

int main(void)
{
  char s[] = "this is first string";
  char t[] = "this";                  /* the original is "first" */ 

  printf("%d", strindex(s, t));

  return 0;
}

int strindex(char *s, char *t)
{
  char *first;
  char *second;
  int pos = 0;

  while (*s != '\0')                  /* the original is "while (*s++ != '\0')", 
                                      it skips the first element in the statement of "if (*s == *t)" */
  {                                   /* ++pos is removed, it also skips the first position */
    if (*s == *t)
    {
      first = s;
      second = t;

      while (*first++ == *second++)
      {
        if (*second == '\0')
          return pos;
      }
    }
    pos++;                            /* add 1 if the condition above not ture */
    s++;                              /* we can move to next character in next loop */
  }

  return -1;
}
