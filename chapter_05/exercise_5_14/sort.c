#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NR_OF_LINES 5000

int is_arg_list_valid(int argc, char *argv[]);

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines);
void write_lines(char *line_ptr[], const size_t nr_of_lines);

void swap(void *v[], size_t i, size_t j);
void q_sort(void *v[], size_t left, size_t right, int (*comp)(void *, void *));

int main(int argc, char *argv[])
{
  if (!is_arg_list_valid(argc, argv))
  {
    puts("ERROR: Invalid arguments.\n");
    return EXIT_FAILURE;
  }

  size_t nr_of_lines;
  char *line_ptr[MAX_NR_OF_LINES];

  if ((nr_of_lines = read_lines(line_ptr, MAX_NR_OF_LINES)) != -1)
  {
    // TODO: Sort the lines.
    q_sort((void **)line_ptr, 0, nr_of_lines - 1, (int (*)(void *, void *))strcmp);
    write_lines(line_ptr, nr_of_lines);
  }
  else
  {
    puts("ERROR: Input too large.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int is_arg_list_valid(int argc, char *argv[])
{
  // TODO: Check if the arg list is valid.
  return 1;
}

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines)
{
  size_t line_length;
  size_t nr_of_lines = 0;
  size_t bufsize = max_nr_of_lines;

  char *current_line = NULL;
  char *current_line_copy = NULL;

  if ((current_line = (char *)malloc(bufsize * sizeof(char))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

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

  return nr_of_lines;
}

void write_lines(char *line_ptr[], const size_t nr_of_lines)
{
  for (size_t i = 0; i < nr_of_lines; ++i)
  {
    puts(line_ptr[i]);
  }
}

void swap(void *v[], size_t i, size_t j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void q_sort(void *v[], size_t left, size_t right, int (*comp)(void *, void *))
{
  if (left - right >= 0)
  {
    return;
  }

  swap(v, left, (left + right) / 2);

  size_t last = left;
  for (size_t i = left + 1; i <= right; ++i)
  {
    if ((*comp)(v[i], v[left]) < 0)
    {
      swap(v, ++last, i);
    }
  }

  swap(v, left, last);
  q_sort(v, left, last - 1, comp);
  q_sort(v, last + 1, right, comp);
}
