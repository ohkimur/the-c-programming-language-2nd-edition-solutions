#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define MAX_NR_OF_LINES 5000

#define MAX_LINE_LEN 1000
#define ALLOC_SIZE 10000

#define MAX_NR_OF_FIELDS 100
#define MAX_NR_OF_FIELD_OPTIONS 4

#define INT_MAX_NR_OF_DIGITS (size_t)(floor(log10(labs(INT_MAX))) + 1)

static char alloc_buf[ALLOC_SIZE];
static char *alloc_p = alloc_buf;

char *alloc(size_t size);
void afree(char *ptr);

size_t get_line(char line[], size_t max_line_len);

int parse_arg_list(int argc, char *argv[]);

size_t str_nth_blank_pos(const char *s, size_t n);
char *substr(const char *s, size_t start, size_t end);
size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines);
void write_lines(char *line_ptr[], const size_t nr_of_lines);

int numcmp(const char *s1, const char *s2);
int estrcmp(const char *s1, const char *s2);
int fieldscmp(const char *s1, const char *s2);
void swap(void *v[], size_t i, size_t j);
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *));

int order = 1;     // 1 ascendent, -1 descendent
int fold = 0;      // 0 case sensitive, 1 case insensitive
int directory = 0; // 0 normal, 1 directory
int (*comp)(const char *, const char *) = estrcmp;

enum field_option
{
  INDEX,
  ORDER,
  FOLD,
  DIRECTORY
};

int nr_of_fields = 0;
int (*fields_comp[MAX_NR_OF_FIELDS])(const char *, const char *);
int fields_options[MAX_NR_OF_FIELDS][MAX_NR_OF_FIELD_OPTIONS];

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
        if (isdigit(argv[i][j]) && !fields_options[i - 1][INDEX])
        {
          char field_index_str[INT_MAX_NR_OF_DIGITS];

          size_t k = 0;
          while (isdigit(argv[i][j]) && j < arg_len && k < INT_MAX_NR_OF_DIGITS)
          {
            field_index_str[k++] = argv[i][j++];
          }
          field_index_str[k] = '\0';

          fields_options[i - 1][INDEX] = atoi(field_index_str);

          --j;
          ++nr_of_fields;
        }
        else
        {
          switch (argv[i][j])
          {
          case 'n':
            comp = numcmp;
            break;

          case 'f':
            fold = 1;
            break;

          case 'd':
            directory = 1;
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

      if (nr_of_fields || argc > 2)
      {
        if (!fields_options[i - 1][INDEX])
        {
          return 0;
        }

        fields_comp[i - 1] = comp;
        fields_options[i - 1][ORDER] = order;
        fields_options[i - 1][FOLD] = fold;
        fields_options[i - 1][DIRECTORY] = directory;

        comp = estrcmp;
        order = 1;
        fold = 0;
        directory = 0;
      }
    }
    else
    {
      return 0;
    }
  }

  if (nr_of_fields && nr_of_fields == argc - 1)
  {
    comp = fieldscmp;
  }
  else if (argc > 2)
  {
    return 0;
  }

  return 1;
}

size_t str_nth_blank_pos(const char *s, size_t n)
{
  size_t pos = 0;
  while (n && *s != '\0')
  {
    if (*s == ' ' || *s == '\t')
    {
      do
      {
        ++pos;
        ++s;
      } while (*s == ' ' || *s == '\t');

      --n;
    }
    else
    {
      ++pos;
      ++s;
    }
  }

  return pos;
}

char *substr(const char *s, size_t start, size_t end)
{
  if (start > end)
  {
    return NULL;
  }

  const size_t len = end - start;
  char *dest = alloc(len + 1);

  for (size_t i = start; i < end && s[i] != '\0'; ++i)
  {
    *dest = s[i];
    ++dest;
  }
  *dest = '\0';

  return dest - len;
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
  while (*s1 != '\0' && *s2 != '\0')
  {
    if (directory)
    {
      while (*s1 != '\0' && !isalnum(*s1) && !isspace(*s1))
      {
        ++s1;
      }
      while (*s2 != '\0' && !isalnum(*s2) && !isspace(*s2))
      {
        ++s2;
      }
    }

    int result = fold ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
    if (result == 0)
    {
      ++s1;
      ++s2;
    }
    else
    {
      return order * result;
    }
  }

  return 0;
}

int fieldscmp(const char *s1, const char *s2)
{
  int i = 0;
  while (i < nr_of_fields)
  {
    size_t start_s1 = str_nth_blank_pos(s1, fields_options[i][INDEX] - 1);
    size_t end_s1 = str_nth_blank_pos(s1, fields_options[i][INDEX]);
    char *field_s1 = substr(s1, start_s1, end_s1);

    size_t start_s2 = str_nth_blank_pos(s2, fields_options[i][INDEX] - 1);
    size_t end_s2 = str_nth_blank_pos(s2, fields_options[i][INDEX]);
    char *field_s2 = substr(s2, start_s2, end_s2);

    comp = fields_comp[i];
    order = fields_options[i][ORDER];
    fold = fields_options[i][FOLD];
    directory = fields_options[i][DIRECTORY];

    int comp_result = comp(field_s1, field_s2);

    afree(field_s1);
    afree(field_s2);

    if (comp_result == 0)
    {
      ++i;
    }
    else
    {
      return comp_result;
    }
  }

  return 0;
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

// NOTE: run: ./sort -3nr -2f < file_in.txt
