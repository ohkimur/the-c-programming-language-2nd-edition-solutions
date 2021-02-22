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
  char nr_of_spaces;
  char tab_len = DEFAULT_TAB_LENGTH;

  int arg_pos = 1;
  int nr_of_custom_tab_stops;
  int initial_nr_of_custom_tab_stops = argc - 1;

  int custom_tab_len;
  int custom_line_offset;

  int i;
  for (i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-')
    {
      custom_line_offset = atoi(argv[i] + 1);
      --initial_nr_of_custom_tab_stops;
    }
    else if (argv[i][0] == '+')
    {
      custom_tab_len = atoi(argv[i] + 1);
      --initial_nr_of_custom_tab_stops;
    }
    else if (!is_str_uint(argv[i]))
    {
      printf("ERROR: The %s argument is not a valid tab stop length. It should be a positive number.", argv[i]);
      return EXIT_FAILURE;
    }
  }

  nr_of_custom_tab_stops = initial_nr_of_custom_tab_stops;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      if (nr_of_custom_tab_stops)
      {
        while (argv[arg_pos][0] == '-' || argv[arg_pos][0] == '+')
        {
          ++arg_pos;
        }

        tab_len = atoi(argv[arg_pos++]);
        --nr_of_custom_tab_stops;
      }
      else if (custom_tab_len && line_pos >= custom_line_offset)
      {
        tab_len = custom_tab_len;
      }
      else
      {
        tab_len = DEFAULT_TAB_LENGTH;
      }

      nr_of_spaces = tab_len;

      while (nr_of_spaces)
      {
        putchar(' ');
        ++line_pos;
        --nr_of_spaces;
      }
    }
    else
    {
      putchar(c);
      ++line_pos;

      if (c == '\n')
      {
        arg_pos = 1;
        line_pos = 0;
        nr_of_custom_tab_stops = initial_nr_of_custom_tab_stops;
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

// NOTE: You can provide a number of tab stops and/ore a custom tab length +n
// after a column -m as command arguments like this:
// ./detab -14 +4 2 8 4 < file_tabs.txt > file_spaces.txt
