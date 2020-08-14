#include <stdio.h>

int main(void)
{
  printf("value of expression: %d", getchar() != EOF);
  return 0;
}

// Exercise page: 31

// NOTE: The expression getchar() != EOF is equal with 1 only if the
// char from the input is != with EOF. An interesting think is that
// on Windows OS the EOF in console is accessible with CTRL+Z command.
