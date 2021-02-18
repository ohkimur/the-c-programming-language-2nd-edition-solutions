#include <stdio.h>

#define DEFAULT_TAB_WIDTH 8

int main(int argc, char *argv[])
{
  int c;
  int line_pos = 0;
  char nr_of_spaces;
  char tab_width = DEFAULT_TAB_WIDTH;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      nr_of_spaces = tab_width - line_pos % tab_width;
      line_pos += nr_of_spaces;

      while (nr_of_spaces)
      {
        putchar(' ');
        --nr_of_spaces;
      }
    }
    else
    {
      putchar(c);

      if (c == '\n')
      {
        line_pos = 0;
      }
      else
      {
        ++line_pos;
      }
    }
  }

  return 0;
}
