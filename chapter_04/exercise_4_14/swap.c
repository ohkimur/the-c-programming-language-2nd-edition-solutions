#include <stdio.h>

#define swap(t, x, y) \
  {                   \
    t temp;           \
    temp = x;         \
    x = y;            \
    y = temp;         \
  };

int main(void)
{
  int x = 2, y = 3;

  printf("x: %d, y: %d\n", x, y);

  swap(int, x, y);
  printf("x: %d, y: %d\n", x, y);

  return 0;
}

// NOTE: A use of a block is very useful because there can be created local
// variables that don't create conflicts with already existed entities.
