#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  // Before changing the world, do this.
  int c;
  while ((c = getc(stdin)) != EOF)
  {
    putc(c, stdout);
  }

  return EXIT_SUCCESS;
}
