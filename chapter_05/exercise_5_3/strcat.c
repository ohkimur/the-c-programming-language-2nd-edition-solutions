#include <stdio.h>

void strcat_ptr(char *s, char *t);

int main(void)
{
  char s[100] = "This is the first string";
  char t[] = ", this second string!";

  strcat_ptr(s, t);

  puts(s);

  return 0;
}

// Concatenate t to end of s; s must be big enough.
void strcat_ptr(char *s, char *t)
{
  // Find the end of s
  while ((*++s) != '\0')
    ;

  // copy t to the end of s
  while ((*s++ = *t++) != '\0')
    ;
}
