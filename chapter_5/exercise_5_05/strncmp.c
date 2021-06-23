#include <stdio.h>

int strcmp_ptr(char *s, char *t, size_t n);

int main(void)
{
  char s[100] = "This is the first string";
  char *t = "This is the second string";
  size_t nr_chars = 13;

  int is_equal = strcmp_ptr(s, t, nr_chars);

  if (is_equal == 0)
  {
    puts("String s is equal with string t.");
  }
  else if (is_equal > 0)
  {
    puts("String s contains more chars than string t.");
  }
  else if (is_equal < 0)
  {
    puts("String s contains less chars than string t.");
  }

  return 0;
}

// Return <0 if s<t, 0 if s==t, >0 if s>t *1
int strcmp_ptr(char *s, char *t, size_t n)
{
  while ((*s == *t) != '\0' && --n)
  {
    if (*s == '\0')
      return 0;

    ++s;
    ++t;
  }

  // If the s string contains more characters than t, then the t char will
  // become '\0' before s char. If this happen then the s char will be >0 and
  // t char will be 0, so the final result will be >0.

  // If the t string contains more character than s, then the s char will
  // become '\0' before t char. If this happen then the s char will be <0 and
  // t char will be 0, so the final result will be <0.

  return *s - *t;
}
