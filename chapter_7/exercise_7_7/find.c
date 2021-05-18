#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000

typedef enum
{
  false,
  true
} boolean;

boolean parse_arg_list(int argc, char *argv[]);

boolean except = false;
boolean number = false;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    exit(EXIT_FAILURE);
  }

  char line[MAX_LINE_LEN];
  size_t line_number = 1;
  while (fgets(line, MAX_LINE_LEN, stdin) != NULL)
  {
    if ((strstr(line, argv[argc - 1]) != NULL) != except)
    {
      if (number)
      {
        printf("%ld: ", line_number);
      }
      printf("%s", line);
    }
    ++line_number;
  }

  exit(EXIT_SUCCESS);
}

boolean parse_arg_list(int argc, char *argv[])
{
  const char *program_name = argv[0];

  while (--argc > 0 && (*++argv)[0] == '-')
  {
    int c;
    while ((c = *++argv[0]))
    {
      switch (c)
      {
      case 'x':
        except = true;
        break;

      case 'n':
        number = true;
        break;

      default:
        fprintf(stderr, "%s: illegal option %c.\n", program_name, c);
        return false;
        break;
      }
    }
  }

  return true;
}
