#include <stdio.h>

int main(void)
{
  char c;
  char last_c;
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

// NOTE: Solution 3 is the most elegant, because is fast and compact.
