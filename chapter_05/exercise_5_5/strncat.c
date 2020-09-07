#include <stdio.h>
#include <string.h>

void strcat_ptr(char *s, char *t, unsigned int n);

int main(void)
{
  char s[100] = "This is the first string";
  char *t = ", this second string!";
  unsigned int nr_chars = 5;

  strcat_ptr(s, t, nr_chars);

  puts(s);

  return 0;
}

// Concatenate t to end of s; s must be big enough.
void strcat_ptr(char *s, char *t, unsigned int n)
{
  // Find the end of s
  unsigned int s_length = strlen(s);

  // Move the s pointer to the end of the s string.
  s += s_length;

  // copy t to the end of s
  while ((*s++ = *t++) != '\0' && n--)
    ;
}
