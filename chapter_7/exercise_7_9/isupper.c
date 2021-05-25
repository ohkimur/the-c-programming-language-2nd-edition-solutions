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
    puts("This letter is lowercase.");
  }

  exit(EXIT_SUCCESS);
}

int is_upper(int c)
{
  return (c >= 'A' && c <= 'Z');
}
