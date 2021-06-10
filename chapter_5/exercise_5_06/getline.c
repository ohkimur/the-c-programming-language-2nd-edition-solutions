#include <stdio.h>

void get_line(char *s);

int main(void)
{
  char string[150] = "";

  get_line(string);
  puts(string);

  return 0;
}

void get_line(char *s)
{
  while ((*s = getchar()) != EOF && (*s != '\n'))
  {
    ++s;
  }

  *s = '\0';
}
