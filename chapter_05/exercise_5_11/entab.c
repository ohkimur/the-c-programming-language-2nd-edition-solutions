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
  int nr_of_spaces = 0;
  char tab_width = DEFAULT_TAB_WIDTH;

  int arg_pos = 1;
  int nr_of_tab_stops = argc;

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
        tab_width = atoi(argv[arg_pos]);
        // --nr_of_tab_stops;
      }
      else if (argc > 1)
      {
        tab_width = 0;
        nr_of_spaces = 0;
      }

      if (tab_width && line_pos % tab_width == 0 && nr_of_spaces > 1)
      {
        printf("%s", argv[arg_pos]);

        if (nr_of_tab_stops)
        {
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

      if (c == '\n')
      {
        line_pos = 0;
        arg_pos = 1;
        nr_of_tab_stops = argc - 1;
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
