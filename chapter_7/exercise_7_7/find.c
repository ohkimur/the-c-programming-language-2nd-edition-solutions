#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000

int parse_arg_list(int argc, char *argv[]);

int except = 0;
int number = 0;
int found = 0;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    exit(EXIT_FAILURE);
  }

  char line[MAX_LINE_LEN];
  size_t line_number = 0;
  while (fgets(line, MAX_LINE_LEN, stdin) != NULL)
  {
    ++line_number;
    if ((strstr(line, argv[argc - 1]) != NULL) != except)
    {
      if (number)
      {
        printf("%ld: ", line_number);
      }
      printf("%s", line);
      ++found;
    }
  }

  exit(EXIT_SUCCESS);
}

int parse_arg_list(int argc, char *argv[])
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
        except = 1;
        break;

      case 'n':
        number = 1;
        break;

      default:
        fprintf(stderr, "%s: illegal option %c.\n", program_name, c);
        argc = 0;
        found = -1;
        break;
      }
    }
  }

  if (argc != 1)
  {
    printf("Usage: find -x -n pattern.\n");
    return 0;
  }

  return 1;
}
