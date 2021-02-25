#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_N_LINES 10

int is_str_uint(char *str);
int is_arg_list_valid(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (!is_arg_list_valid(argc, argv))
  {
    puts("ERROR: Invalid arguments.\n");
    return EXIT_FAILURE;
  }

  unsigned int n_lines = DEFAULT_N_LINES;

  if (argc == 2)
  {
    n_lines = atoi(argv[argc - 1] + 1);
  }

  printf("%d", n_lines);

  return EXIT_SUCCESS;
}

int is_str_uint(char *str)
{
  for (unsigned int i = 0; i < strlen(str); ++i)
  {
    if (!isdigit(str[i]))
    {
      return 0;
    }
  }
  return 1;
}

int is_arg_list_valid(int argc, char *argv[])
{
  if (argc > 2 || (argc == 2 && (argv[argc - 1][0] != '-' || !is_str_uint(argv[argc - 1] + 1))))
  {
    return 0;
  }
  return 1;
}
