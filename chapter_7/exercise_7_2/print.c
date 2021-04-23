#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_ascii(int c);

int main(int argc, char *argv[])
{
  // Before changing the world, do this.
  int c;
  while ((c = getc(stdin)) != EOF)
  {
    if (is_ascii(c))
    {
      putc(c, stdout);
    }
    else
    {
      putc('#', stdout);
    }
  }

  return EXIT_SUCCESS;
}

int is_ascii(int c)
{
  if (c > 127)
  {
    return 0;
  }

  return 1;
}
