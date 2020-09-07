#include <stdio.h>

int main(void)
{
  char c;
  char last_c;
  while ((c = getchar()) != EOF)
  {
    // Solution 1
    // if(c != ' ')
    // {
    //   putchar(c);
    // }
    // else if(last_c != ' ')
    // {
    //   putchar(c);
    // }

    // Solution 2
    // if(!(c == ' ' && last_c == ' '))
    // {
    //   putchar(c);
    // }

    // Solution 3
    if (c != ' ' || last_c != ' ')
    {
      putchar(c);
    }

    last_c = c;
  }

  return 0;
}


// NOTE: Solution 3 is the most elegant, because is fast and compact.
