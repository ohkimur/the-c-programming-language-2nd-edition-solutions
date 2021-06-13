#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
  false,
  true
} boolean;

typedef int (*convert_fn_t)(int);

boolean parse_arg_list(int argc, char *argv[]);
void consume_input(convert_fn_t convert);

convert_fn_t convert;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
    return EXIT_FAILURE;
  }

  consume_input(convert);

  return EXIT_SUCCESS;
}

boolean parse_arg_list(int argc, char *argv[])
{
  if (strcmp(argv[0], "lower") == 0)
  {
    convert = tolower;
    return true;
  }
  else if (strcmp(argv[0], "upper") == 0)
  {
    convert = toupper;
    return true;
  }

  return false;
}

void consume_input(convert_fn_t convert)
{
  int c;
  while ((c = getc(stdin)) != EOF)
  {
    putc(convert(c), stdout);
  }
}

// NOTE: run: ( exec -a upper ./case < case.c )
// It is possible to change argv[0] by using the exec command.
