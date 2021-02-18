#include <stdio.h>

#define TAB_WIDTH 8

int main(void)
{
  int c;
  int line_pos = 0;
  int nr_of_tabs;
  int nr_of_spaces = 0;

  while ((c = getchar()) != EOF)
  {
    ++line_pos;

    if (c == ' ')
    {
      ++nr_of_spaces;
    }
    else
    {
      if (nr_of_spaces == 1)
      {
        putchar(' ');
      }
      else if (nr_of_spaces > 1)
      {
        nr_of_tabs = line_pos / TAB_WIDTH - (line_pos - nr_of_spaces) / TAB_WIDTH;

        while (nr_of_tabs)
        {
          putchar('\t');
          --nr_of_tabs;
        }
      }

      putchar(c);

      if (c == '\n')
      {
        line_pos = 0;
      }

      nr_of_spaces = 0;
    }
  }

  return 0;
}
