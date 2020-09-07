#include <stdio.h>

int main(void)
{
  printf("value of expression: %d", getchar() != EOF);
  return 0;
}


// NOTE: The expression getchar() != EOF is equal with 1 only if input char
// is != with EOF. An interesting thing is that on Windows the console EOF is
// accessible with CTRL+Z command.
