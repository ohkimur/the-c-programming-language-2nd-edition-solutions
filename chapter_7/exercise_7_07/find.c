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
void find_pattern(char *pattern, FILE *file_p);

char *program_name;

boolean except = false;
boolean number = false;

int pattern_arg_pos = 1;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    exit(EXIT_FAILURE);
  }

  if (argc - pattern_arg_pos > 1)
  {
    for (int file_arg_pos = pattern_arg_pos + 1; file_arg_pos < argc; file_arg_pos++)
    {
      FILE *file_p;
      if ((file_p = fopen(argv[file_arg_pos], "r")) == NULL)
      {
        fprintf(stderr, "%s: can't open %s.\n", program_name, argv[file_arg_pos]);
        exit(EXIT_FAILURE);
      }
      printf("%s\n", argv[file_arg_pos]);
      find_pattern(argv[pattern_arg_pos], file_p);
      fclose(file_p);

      if (file_arg_pos < argc - 1)
      {
        putc('\n', stdout);
      }
    }
  }
  else
  {
    find_pattern(argv[pattern_arg_pos], stdin);
  }

  exit(EXIT_SUCCESS);
}

boolean parse_arg_list(int argc, char *argv[])
{
  program_name = argv[0];

  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s [-xn]... PATTERN [FILE]...\n", program_name);
    return false;
  }

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

    ++pattern_arg_pos;
  }

  return true;
}

void find_pattern(char *pattern, FILE *file_p)
{
  size_t line_number = 1;
  char line[MAX_LINE_LEN];
  while (fgets(line, MAX_LINE_LEN, file_p) != NULL)
  {
    if ((strstr(line, pattern) != NULL) != except)
    {
      if (number)
      {
        printf("%ld: ", line_number);
      }
      printf("%s", line);
    }
    ++line_number;
  }
}

// NOTE: run: ./find -n "Some people" file_1.txt file_2.txt
