#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NR_OF_LINES 5000
#define DEFAULT_NR_OF_LINES_TO_PRINT 10

#define MAX_LINE_LEN 1000
#define ALLOC_SIZE 10000

static char alloc_buf[ALLOC_SIZE];
static char *alloc_p = alloc_buf;

char *alloc(size_t size);
void afree(char *ptr);

size_t get_line(char line[], size_t max_line_len);

int is_str_uint(char *str);
int is_arg_list_valid(int argc, char *argv[]);

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines);
void write_lines(char *line_ptr[], const size_t nr_of_lines_to_print, const size_t total_nr_of_lines);

int main(int argc, char *argv[])
{
  if (!is_arg_list_valid(argc, argv))
  {
    puts("Error: invalid arguments.\n");
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
    puts("Error: input too large.\n");
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

size_t get_line(char line[], size_t max_line_len)
{
  int c;
  size_t i;

  for (i = 0; i < max_line_len - 1 && (c = getc(stdin)) != EOF && c != '\n'; ++i)
  {
    line[i] = c;
  }

  if (c == '\n')
  {
    line[i] = c;
    ++i;
  }

  line[i] = '\0';

  return i;
}

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines)
{
  size_t line_length;
  size_t nr_of_lines = 0;

  char *current_line = alloc(MAX_LINE_LEN);
  char *current_line_copy = NULL;

  while ((line_length = get_line(current_line, MAX_LINE_LEN)))
  {
    if (nr_of_lines >= max_nr_of_lines || (current_line_copy = alloc(line_length)) == NULL)
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

  afree(current_line);

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
    afree(line_ptr[i]);
  }
}

char *alloc(size_t size)
{
  if (alloc_buf + ALLOC_SIZE - alloc_p >= size)
  {
    alloc_p += size;
    return alloc_p - size;
  }

  return NULL;
}

void afree(char *ptr)
{
  if (ptr >= alloc_buf && ptr < alloc_buf + ALLOC_SIZE)
  {
    alloc_p = ptr;
  }
}

// NOTE: run: ./tail -5 < file_in.txt
