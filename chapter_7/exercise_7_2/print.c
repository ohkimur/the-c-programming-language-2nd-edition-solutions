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
  while ((c = getc(stdin)) != EOF)
  {
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

    // TODO: Break the lines that are too long. You can remember the last blank
    // and after hitting the break point you unget characters back to the last
    // blank. Replace the last blank with \n.
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
