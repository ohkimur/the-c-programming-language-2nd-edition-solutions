#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEFAULT_TAB_WIDTH 8

int is_str_uint(const char *str);

int main(int argc, char *argv[])
{
  int c;
  int line_pos = 0;
  int nr_of_tabs = 0;
  int nr_of_spaces = 0;
  int line_start_pos = 0;
  char tab_width = DEFAULT_TAB_WIDTH;

  int i;
  for (i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '+')
    {
      if (!is_str_uint(argv[i] + 1))
      {
        printf("ERROR: The %s argument is not a valid tab stop length. It should be a positive number.", argv[i]);
        return EXIT_FAILURE;
      }
      else
      {
        tab_width = atoi(argv[i] + 1);
      }
    }
    else if (argv[i][0] == '-')
    {
      if (!is_str_uint(argv[i] + 1))
      {
        printf("ERROR: The %s argument is not a valid column position. It should be a positive number.", argv[i]);
        return EXIT_FAILURE;
      }
      else
      {
        line_start_pos = atoi(argv[i] + 1);
      }
    }
  }

  while ((c = getchar()) != EOF)
  {
    ++line_pos;

    if (c == ' ')
    {
      ++nr_of_spaces;

      if (tab_width && line_pos > line_start_pos && line_pos % tab_width == 0 && nr_of_spaces > 1)
      {
        // TODO: Make sure you add a new tab only when the number of spaces is larger than a tab length.
        // run this to see the problem: ./entab  +8 -6 < file_spaces.txt > file_tabs.txt
        ++nr_of_tabs;
        nr_of_spaces = line_start_pos;
      }
    }
    else
    {
      while (nr_of_spaces)
      {
        putchar(' ');
        --nr_of_spaces;
      }

      while (nr_of_tabs)
      {
        putchar('\t');
        --nr_of_tabs;
      }

      if (c == '\n')
      {
        line_pos = 0;
      }

      putchar(c);
    }
  }

  return EXIT_SUCCESS;
}

int is_str_uint(const char *str)
{
  int i;
  for (i = 0; i < strlen(str); i++)
  {
    if (!isdigit(str[i]))
    {
      return 0;
    }
  }

  return 1;
}
