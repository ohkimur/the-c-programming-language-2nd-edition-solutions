#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000

typedef enum
{
  false,
  true
} boolean;

boolean parse_arg_list(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    exit(EXIT_FAILURE);
  }

  char line[MAX_LINE_LEN];

  while (--argc > 0)
  {
    FILE *file_p;
    if ((file_p = fopen(*++argv, "r")) == NULL)
    {
      fprintf(stderr, "print: can't open %s.\n", *argv);
      exit(EXIT_FAILURE);
    }

    printf("%s\n", *argv);

    while (fgets(line, MAX_LINE_LEN, file_p) != NULL)
    {
      printf("%s", line);
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
