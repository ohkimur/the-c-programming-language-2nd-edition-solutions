#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NR_OF_LINES 5000
#define DEFAULT_NR_OF_LINES_TO_PRINT 10

int is_str_uint(char *str);
int is_arg_list_valid(int argc, char *argv[]);

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines);
void write_lines(char *line_ptr[], const size_t nr_of_lines_to_print, const size_t total_nr_of_lines);

int main(int argc, char *argv[])
{
  if (!is_arg_list_valid(argc, argv))
  {
    puts("ERROR: Invalid arguments.\n");
    return EXIT_FAILURE;
  }

  size_t nr_of_lines_to_print = DEFAULT_NR_OF_LINES_TO_PRINT;

  if (argc == 2)
  {
    nr_of_lines_to_print = atoi(argv[argc - 1] + 1);
  }

  size_t total_nr_of_lines;
  char *line_ptr[MAX_NR_OF_LINES];

  if ((total_nr_of_lines = read_lines(line_ptr, MAX_NR_OF_LINES)) != -1)
  {
    write_lines(line_ptr, nr_of_lines_to_print, total_nr_of_lines);
  }
  else
  {
    puts("ERROR: Input too large.\n");
    return EXIT_FAILURE;
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
  if (argc > 2 || (argc == 2 && (argv[argc - 1][0] != '-' || !is_str_uint(argv[argc - 1] + 1))))
  {
    return 0;
  }
  return 1;
}

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines)
{
  size_t line_length;
  size_t nr_of_lines = 0;
  size_t bufsize = 0;

  char *current_line = NULL;
  char *current_line_copy = NULL;

  while ((line_length = getline(&current_line, &bufsize, stdin)) != -1)
  {
    if (nr_of_lines >= max_nr_of_lines || (current_line_copy = (char *)malloc(line_length * sizeof(char))) == NULL)
    {
      return -1;
    }
    else
    {
      current_line[line_length - 1] = '\0';
      strcpy(current_line_copy, current_line);
      line_ptr[nr_of_lines++] = current_line_copy;
    }
  }

  free(current_line);

  return nr_of_lines;
}

void write_lines(char *line_ptr[], const size_t nr_of_lines_to_print, const size_t total_nr_of_lines)
{
  size_t start_pos = 0;

  if (total_nr_of_lines >= nr_of_lines_to_print)
  {
    start_pos = total_nr_of_lines - nr_of_lines_to_print;
  }

  for (size_t i = start_pos; i < total_nr_of_lines; ++i)
  {
    puts(line_ptr[i]);
    free(line_ptr[i]);
  }
}

// NOTE: run: ./tail -5 < file_in.txt
