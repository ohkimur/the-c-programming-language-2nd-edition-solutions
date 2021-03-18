#include <stdio.h>
#include <string.h>

void reverse(char *s);

int main(void)
{
  char s[100] = "test";

  reverse(s);
  puts(s);

  return 0;
}

void reverse(char *s)
{
  char *t = s + strlen(s) - 1;
  char aux = 0;

  if (*s == '\0')
    return;

  while (s < t)
  {
    aux = *t;
    *t-- = *s;
    *s++ = aux;
  }
}
