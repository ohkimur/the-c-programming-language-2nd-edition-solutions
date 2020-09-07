#include <stdio.h>

void strcpy_ptr(char *s, char *t, unsigned int n);

int main(void)
{
  char s[100] = "This is the first string";
  char *t = "Test is the second string, that is cool";
  unsigned int nr_chars = 26;

  strcpy_ptr(s, t, nr_chars);

  puts(s);

  return 0;
}

void strcpy_ptr(char *s, char *t, unsigned int n)
{
  while ((*s++ = *t++) && --n)
    ;
  ;
}
