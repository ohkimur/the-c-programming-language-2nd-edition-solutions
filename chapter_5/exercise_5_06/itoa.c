#include <stdio.h>
#include <string.h>

void reverse(char *s);
void itoa(char *s, int n);

int main(void)
{
  int i = 1234;
  char s[100] = "";

  itoa(s, i);

  printf("itoa: %s\n", s);

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

void itoa(char *s, int n)
{
  char *t = s;

  while (n)
  {
    *(t++) = n % 10 + '0';
    n /= 10;
  }

  *t = '\0';

  reverse(s);
}
