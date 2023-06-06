#include <stdio.h>

int main(void)
{
  char c;

  while ((c = getchar()) != EOF)
  {
    if (c == ' ' || c == '\t' || c == '\n')
    {
      putchar('\n');
    }
    else
    {
      putchar(c);
    }
  }

  return 0;
}
