#include <stdio.h>

int main(void)
{
  printf("hello: \c");
  return 0;
}

// Exercise page: 22

// NOTE: The compiler doesn't recognize the '\o' as an escape
// sequence and throws a warning to let us know that.
