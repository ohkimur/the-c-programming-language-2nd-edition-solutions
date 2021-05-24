#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_upper(int c);

int main(int argc, char *argv[])
{
  if (is_upper('c'))
  {
    puts("This letter is uppercase.");
  }
  else
  {
    puts("This is lowercase.");
  }

  exit(EXIT_SUCCESS);
}

int is_upper(int c)
{
  if (c >= 'A' && c <= 'Z')
  {
    return 1;
  }

  return 0;
}
