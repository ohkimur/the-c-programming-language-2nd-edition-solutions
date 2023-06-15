#include <stdio.h>

int main(void)
{
  int c;
  int last_c = '\0';
  /*
    If I use chars here instead of ints I get a "comparison
    between pointer and integer gcc" warning.
    getchar returns int not char.
    Char type is de facto a 1-byte integer type.
    Thank you for you solutions, they're helping me learn.
  */
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
