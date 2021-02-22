#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEFAULT_TAB_LENGTH 8

int is_str_uint(const char *str);

int main(int argc, char *argv[])
{
  int c;
  int line_pos = 0;
  int nr_of_spaces = 0;
  char tab_len = DEFAULT_TAB_LENGTH;

  int arg_pos = 1;
  int nr_of_tab_stops = argc - 1;

  int i;
  for (i = 1; i < argc; ++i)
  {
    if (!is_str_uint(argv[i]))
    {
      printf("ERROR: The %s argument is not a valid tab stop length. It should be a positive number.", argv[i]);
      return EXIT_FAILURE;
    }
  }

  while ((c = getchar()) != EOF)
  {
    ++line_pos;

    if (c == ' ')
    {
      ++nr_of_spaces;

      if (nr_of_tab_stops)
      {
        tab_len = atoi(argv[arg_pos]);
      }
      else if (argc > 1)
      {
        tab_len = DEFAULT_TAB_LENGTH;
      }

      if (tab_len && line_pos % tab_len == 0 && nr_of_spaces > 1)
      {
        if (nr_of_tab_stops)
        {
          line_pos -= tab_len;
          ++arg_pos;
          --nr_of_tab_stops;
        }

        putchar('\t');
        nr_of_spaces = 0;
      }
    }
    else
    {
      while (nr_of_spaces)
      {
        putchar(' ');
        --nr_of_spaces;
      }

      putchar(c);

      if (c == '\n')
      {
        line_pos = 0;
        arg_pos = 1;
        nr_of_tab_stops = argc - 1;
      }
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

// NOTE: You can provide a number of tab stops as command arguments like this:
// ./entab 2 8 4 < file_spaces.txt > file_tabs.txt
