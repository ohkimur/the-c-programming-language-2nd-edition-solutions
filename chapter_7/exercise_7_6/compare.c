#include <stdio.h>
#include <stdlib.h>

int parse_arg_list(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
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
