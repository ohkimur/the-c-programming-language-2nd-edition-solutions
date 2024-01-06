#include <stdio.h>

int main()
{
  int c, prev;
  prev = EOF;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      if (prev != ' ' && prev != '\t' && prev != '\n') {
        putchar('\n');
      }
    }
    else {
      putchar(c);
    }

    prev = c;
  }

  return 0;
}
