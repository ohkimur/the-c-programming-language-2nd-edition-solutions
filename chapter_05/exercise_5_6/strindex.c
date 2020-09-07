#include <stdio.h>

int strindex(char *s, char *t);

int main(void)
{
  char s[] = "this is first string";
  char t[] = "first";

  printf("%d", strindex(s, t));

  return 0;
}

int strindex(char *s, char *t)
{
  char *first;
  char *second;
  int pos = 0;

  while (*s++ != '\0')
  {
    ++pos;

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
  }

  return -1;
}

