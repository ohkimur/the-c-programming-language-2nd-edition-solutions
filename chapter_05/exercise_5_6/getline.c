#include <stdio.h>

void getln(char *s);

int main(void)
{
  char string[150] = "";

  getln(string);
  puts(string);

  return 0;
}

void getln(char *s)
{
  while ((*s = getchar()) != EOF && (*s != '\n'))
  {
    ++s;
  }

  *s = '\0';
}

