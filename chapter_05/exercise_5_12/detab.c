#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_TAB_LENGTH 8

int is_str_uint(char *str);
int is_arg_list_valid(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!is_arg_list_valid(argc, argv))
  {
    puts("Error: invalid arguments.\n");
    return EXIT_FAILURE;
  }

  int c;
  size_t arg_pos = 1;
  size_t line_pos = 0;
  size_t tab_stop = DEFAULT_TAB_LENGTH;
  size_t nr_of_spaces;
  size_t nr_of_custom_tab_stops;
  size_t initial_nr_of_custom_tab_stops = argc - 1;

  size_t custom_tab_stop = 0;
  size_t custom_line_pos_start = 0;

  for (size_t i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      custom_line_pos_start = atoi(argv[i] + 1);
      --initial_nr_of_custom_tab_stops;
    }
    else if (argv[i][0] == '+')
    {
      custom_tab_stop = atoi(argv[i] + 1);
      --initial_nr_of_custom_tab_stops;
    }
  }

  nr_of_custom_tab_stops = initial_nr_of_custom_tab_stops;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      if (nr_of_custom_tab_stops)
      {
        tab_stop = atoi(argv[arg_pos++]);
        --nr_of_custom_tab_stops;
      }
      else if (custom_tab_stop)
      {
        tab_stop = custom_tab_stop;
      }
      else if (initial_nr_of_custom_tab_stops)
      {
        tab_stop = 1;
      }

      if (custom_line_pos_start)
      {
        if (line_pos >= custom_line_pos_start)
        {
          nr_of_spaces = tab_stop;
        }
        else
        {
          nr_of_spaces = 1;
        }
      }
      else
      {
        nr_of_spaces = tab_stop - line_pos % tab_stop;
      }

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

int is_str_uint(char *str)
{
  for (size_t i = 0; i < strlen(str); ++i)
  {
    if (!isdigit(str[i]))
    {
      return 0;
    }
  }
  return 1;
}

int is_arg_list_valid(int argc, char *argv[])
{
  for (size_t i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-' || argv[i][0] == '+')
    {
      if (argc > 3 || !is_str_uint(argv[i] + 1))
      {
        return 0;
      }
      continue;
    }

    if (!is_str_uint(argv[i]) || (i > 1 && atoi(argv[i - 1]) > atoi(argv[i])))
    {
      return 0;
    }
  }
  return 1;
}

// NOTE: The current program works in a similar fashion as expand.
// run: ./detab 4 8 12 16 < file_tabs.txt > file_spaces.txt
// run: ./detab +8 -2 < file_tabs.txt > file_spaces.txt
