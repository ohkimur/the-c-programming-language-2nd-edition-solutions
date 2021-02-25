#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_N_LINES 10
#define MAX_LINE_LENGTH 1000

int is_str_uint(char *str);
int is_arg_list_valid(int argc, char *argv[]);

size_t read_lines(char *line_ptr[], size_t max_nr_of_lines);
void write_lines(char *line_ptr[], const size_t nr_of_lines);

int main(int argc, char *argv[])
{
  if (!is_arg_list_valid(argc, argv))
  {
    puts("ERROR: Invalid arguments.\n");
    return EXIT_FAILURE;
  }

  unsigned int nr_of_lines_to_print = DEFAULT_N_LINES;

  if (argc == 2)
  {
    nr_of_lines_to_print = atoi(argv[argc - 1] + 1);
  }

  int nr_of_lines;
  char *line_ptr[MAX_LINE_LENGTH];

  if ((nr_of_lines = read_lines(line_ptr, MAX_LINE_LENGTH)) != -1)
  {
    write_lines(line_ptr, nr_of_lines);
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
  for (unsigned int i = 0; i < strlen(str); ++i)
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

size_t read_lines(char *line_ptr[], size_t max_nr_of_lines)
{
  size_t line_length;
  size_t nr_of_lines = 0;
  size_t bufsize = MAX_LINE_LENGTH;

  char *p = NULL;
  char *line = NULL;

  if ((line = (char *)malloc(bufsize * sizeof(char))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  while ((line_length = getline(&line, &bufsize, stdin)) != -1)
  {
    if (nr_of_lines >= max_nr_of_lines || (p = (char *)malloc(line_length * sizeof(char))) == NULL)
    {
      return -1;
    }
    else
    {
      line[line_length - 1] = '\0';
      strcpy(p, line);
      line_ptr[nr_of_lines++] = p;
    }
  }

  return nr_of_lines;
}

void write_lines(char *line_ptr[], const size_t nr_of_lines)
{
  for (size_t i = 0; i < nr_of_lines; ++i)
  {
    puts(line_ptr[i]);
  }
}
