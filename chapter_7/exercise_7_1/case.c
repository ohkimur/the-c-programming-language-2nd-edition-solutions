#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum __BOOL
{
  FALSE,
  TRUE
} boolean;

boolean lower = TRUE;
boolean parse_arg_list(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
    return EXIT_FAILURE;
  }

  int c;
  if (lower)
  {
    while ((c = getc(stdin)) != EOF)
    {
      putc(tolower(c), stdout);
    }
  }
  else
  {
    while ((c = getc(stdin)) != EOF)
    {
      putc(toupper(c), stdout);
    }
  }

  return EXIT_SUCCESS;
}

boolean parse_arg_list(int argc, char *argv[])
{
  if (strcmp(argv[0], "lower") == 0)
  {
    lower = TRUE;
    return TRUE;
  }
  else if (strcmp(argv[0], "upper") == 0)
  {
    lower = FALSE;
    return TRUE;
  }

  return FALSE;
}
