#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
