#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_upper_v1(int c);
int is_upper_v2(int c);

int main(int argc, char *argv[])
{
  if (is_upper_v1('c'))
  {
    puts("is_upper_v1: This letter is uppercase.");
  }
  else
  {
    puts("is_upper_v1: This letter is lowercase.");
  }

  if (is_upper_v2('c'))
  {
    puts("is_upper_v2: This letter is uppercase.");
  }
  else
  {
    puts("is_upper_v2: This letter is lowercase.");
  }

  exit(EXIT_SUCCESS);
}

int is_upper_v1(int c)
{
  return (c >= 'A' && c <= 'Z');
}

int is_upper_v2(int c)
{
  return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}
