#include <stdio.h>

int main(void)
{
  char c;
  char last_c = '\0';
  while ((c = getchar()) != EOF)
  {
    if (c != ' ' || last_c != ' ')
    {
      putchar(c);
    }

    last_c = c;
  }

  return 0;
}
