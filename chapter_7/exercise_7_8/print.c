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
  return true;
}
