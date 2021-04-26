#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 80

typedef enum
{
  false,
  true
} boolean;

boolean parse_arg_list(int argc, char *argv[]);
int is_ascii(int c);

boolean octal = true;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
    return EXIT_FAILURE;
  }

  int c;
  size_t col_pos = 1;
  while ((c = getc(stdin)) != EOF)
  {
    ++col_pos;

    if (is_ascii(c))
    {
      putc(c, stdout);
    }
    else
    {
      if (octal)
      {
        printf("\\%o", c);
      }
      else
      {
        printf("\\%x", c);
      }
    }

    if (c == '\n')
    {
      col_pos = 1;
    }

    if (col_pos >= MAX_LINE_LEN)
    {
      if (isblank(c))
      {
        col_pos = 1;
        putc('\n', stdout);
      }
    }
  }

  return EXIT_SUCCESS;
}

boolean parse_arg_list(int argc, char *argv[])
{
  if (argc == 2)
  {
    if (strcmp(argv[1], "-o") == 0)
    {
      octal = true;
      return true;
    }
    else if (strcmp(argv[1], "-x") == 0)
    {
      octal = false;
      return true;
    }
  }

  return false;
}

int is_ascii(int c)
{
  if (c > 127)
  {
    return 0;
  }

  return 1;
}
