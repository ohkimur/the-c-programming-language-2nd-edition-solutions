#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000

int parse_arg_list(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    fprintf(stderr, "Error: invalid arguments.\n");
    exit(EXIT_FAILURE);
  }

  char *program_name = argv[0];

  FILE *file_1;
  FILE *file_2;

  if ((file_1 = fopen(argv[1], "r")) == NULL)
  {
    fprintf(stderr, "%s: can't open %s.\n", program_name, argv[1]);
    exit(EXIT_FAILURE);
  }

  if ((file_2 = fopen(argv[2], "r")) == NULL)
  {
    fprintf(stderr, "%s: can't open %s.\n", program_name, argv[2]);
    exit(EXIT_FAILURE);
  }

  char line_1[MAX_LINE_LEN];
  char line_2[MAX_LINE_LEN];

  size_t line_number = 1;
  while (fgets(line_1, MAX_LINE_LEN, file_1) != NULL && fgets(line_2, MAX_LINE_LEN, file_2) != NULL)
  {
    if (strcmp(line_1, line_2) != 0)
    {
      printf("%s [%zu]: %s", argv[1], line_number, line_1);
      fclose(file_1);

      printf("%s [%zu]: %s", argv[2], line_number, line_2);
      fclose(file_2);
      break;
    }

    ++line_number;
  }

  exit(EXIT_SUCCESS);
}

int parse_arg_list(int argc, char *argv[])
{
  if (argc != 3)
  {
    return 0;
  }

  return 1;
}

// NOTE: run: ./compare file_1.txt file_2.txt
