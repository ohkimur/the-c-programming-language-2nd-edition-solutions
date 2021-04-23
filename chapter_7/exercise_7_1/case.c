#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
  false,
  true
} boolean;

boolean parse_arg_list(int argc, char *argv[]);
void consume_input(int (*char_transform)(int));

int (*char_transform)(int);

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
    return EXIT_FAILURE;
  }

  consume_input(char_transform);

  return EXIT_SUCCESS;
}

boolean parse_arg_list(int argc, char *argv[])
{
  if (strcmp(argv[0], "lower") == 0)
  {
    char_transform = tolower;
    return true;
  }
  else if (strcmp(argv[0], "upper") == 0)
  {
    char_transform = toupper;
    return true;
  }

  return false;
}

void consume_input(int (*char_transform)(int))
{
  int c;
  while ((c = getc(stdin)) != EOF)
  {
    putc(char_transform(c), stdout);
  }
}

// NOTE: run: ( exec -a upper ./case < case.c )
// It is possible to change argv[0] by using the exec command.
