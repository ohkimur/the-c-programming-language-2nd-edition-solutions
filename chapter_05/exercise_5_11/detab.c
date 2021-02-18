#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TAB_WIDTH 8

int main(int argc, char *argv[])
{
  int c;
  int line_pos = 0;
  char nr_of_spaces;
  char tab_width = DEFAULT_TAB_WIDTH;

  int arg_pos = 0;
  int nr_of_tab_stops = argc - 1;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      if (nr_of_tab_stops)
      {
        tab_width = atoi(argv[++arg_pos]);
        --nr_of_tab_stops;
      }
      else if (argc > 1)
      {
        tab_width = 0;
      }

      nr_of_spaces = tab_width ? tab_width - line_pos % tab_width : 0;

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
        arg_pos = 0;
        nr_of_tab_stops = argc - 1;
      }
      else
      {
        ++line_pos;
      }
    }
  }

  return 0;
}
