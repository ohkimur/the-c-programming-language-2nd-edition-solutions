#include <stdio.h>

#define TAB_WIDTH 8

int main(void)
{
  int c;
  int col = 0;
  char spaces;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      spaces = TAB_WIDTH - col % TAB_WIDTH;
      col += spaces;

      while (spaces)
      {
        putchar(' ');
        --spaces;
      }
    }
    else
    {
      putchar(c);

      if (c == '\n')
      {
        col = 0;
      }
      else
      {
        ++col;
      }
    }
  }

  return 0;
}
