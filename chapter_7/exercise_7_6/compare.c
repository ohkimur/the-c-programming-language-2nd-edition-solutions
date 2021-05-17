#include <stdio.h>
#include <stdlib.h>

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

  exit(EXIT_SUCCESS);
}

int parse_arg_list(int argc, char *argv[])
{
  if (argc < 3)
  {
    return 0;
  }

  return 1;
}
