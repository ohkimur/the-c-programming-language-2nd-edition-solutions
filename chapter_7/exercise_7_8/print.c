#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000
#define LINES_PER_PAGE 10

typedef enum
{
  false,
  true
} boolean;

boolean parse_arg_list(int argc, char *argv[]);
void print_file(char *file_name);

char *program_name;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    exit(EXIT_FAILURE);
  }

  while (--argc > 0)
  {
    print_file(*++argv);

    if (argc != 1)
    {
      putc('\n', stdout);
    }
  }

  exit(EXIT_SUCCESS);
}

boolean parse_arg_list(int argc, char *argv[])
{
  const char *program_name = argv[0];

  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s [FILE]...\n", program_name);
    return false;
  }

  return true;
}

void print_file(char *file_name)
{
  FILE *file_p;
  if ((file_p = fopen(file_name, "r")) == NULL)
  {
    fprintf(stderr, "%s: can't open %s.\n", program_name, file_name);
    exit(EXIT_FAILURE);
  }

  size_t line_number = 1;
  char line[MAX_LINE_LEN];
  while (fgets(line, MAX_LINE_LEN, file_p) != NULL)
  {
    if ((line_number - 1) % LINES_PER_PAGE == 0)
    {
      printf("[%s]: page %zu\n", file_name, line_number / LINES_PER_PAGE + 1);
    }

    printf("%zu: %s", line_number, line);
    ++line_number;
  }
}

// NOTE: run: ./print ../exercise_7_7/file_1.txt ../exercise_7_7/file_2.txt ./print.c
