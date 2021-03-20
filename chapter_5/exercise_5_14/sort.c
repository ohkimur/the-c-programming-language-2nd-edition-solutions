#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NR_OF_LINES 5000

#define MAX_LINE_LEN 1000
#define ALLOC_SIZE 10000

static char alloc_buf[ALLOC_SIZE];
static char *alloc_p = alloc_buf;

char *alloc(size_t size);
void afree(char *ptr);

size_t get_line(char line[], size_t max_line_len);

int parse_arg_list(int argc, char *argv[]);

size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines);
void write_lines(char *line_ptr[], const size_t nr_of_lines);

int numcmp(const char *s1, const char *s2);
int estrcmp(const char *s1, const char *s2);
void swap(void *v[], size_t i, size_t j);
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *));

int order = 1; // 1 ascendent, -1 descendent
int (*comp)(const char *, const char *) = estrcmp;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
    return EXIT_FAILURE;
  }

  size_t nr_of_lines;
  char *line_ptr[MAX_NR_OF_LINES];

  if ((nr_of_lines = read_lines(line_ptr, MAX_NR_OF_LINES)) != -1)
  {
    quick_sort((void **)line_ptr, 0, nr_of_lines - 1, (int (*)(void *, void *))comp);
    write_lines(line_ptr, nr_of_lines);
  }
  else
  {
    puts("Error: input too large.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int parse_arg_list(int argc, char *argv[])
{
  for (int i = 1; i < argc; ++i)
  {
    size_t arg_len = strlen(argv[i]);
    if (arg_len > 1 && argv[i][0] == '-')
    {
      for (size_t j = 1; j < arg_len; ++j)
      {
        switch (argv[i][j])
        {
        case 'n':
          comp = numcmp;
          break;

        case 'r':
          order = -1;
          break;

        default:
          return 0;
          break;
        }
      }
    }
    else
    {
      return 0;
    }
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

void write_lines(char *line_ptr[], const size_t nr_of_lines)
{
  for (size_t i = 0; i < nr_of_lines; ++i)
  {
    puts(line_ptr[i]);
    afree(line_ptr[i]);
  }
}

int numcmp(const char *s1, const char *s2)
{
  double nr1 = atof(s1);
  double nr2 = atof(s2);

  if (nr1 < nr2)
  {
    return order * -1;
  }
  else if (nr1 > nr2)
  {
    return order * 1;
  }

  return 0;
}

int estrcmp(const char *s1, const char *s2)
{
  return order * strcmp(s1, s2);
}

void swap(void *v[], size_t i, size_t j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *))
{
  if ((long)start >= (long)end)
  {
    return;
  }

  swap(v, start, (start + end) / 2);

  size_t last = start;
  for (size_t i = start + 1; i <= end; ++i)
  {
    if ((*comp)(v[i], v[start]) < 0)
    {
      swap(v, ++last, i);
    }
  }

  swap(v, start, last);
  quick_sort(v, start, last - 1, comp);
  quick_sort(v, last + 1, end, comp);
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

// NOTE: run: ./sort -nr < file_in.txt
