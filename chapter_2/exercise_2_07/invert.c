#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)   \
  (byte & 128 ? '1' : '0'),    \
      (byte & 64 ? '1' : '0'), \
      (byte & 32 ? '1' : '0'), \
      (byte & 16 ? '1' : '0'), \
      (byte & 8 ? '1' : '0'),  \
      (byte & 4 ? '1' : '0'),  \
      (byte & 2 ? '1' : '0'),  \
      (byte & 1 ? '1' : '0')

unsigned int invert(int x, int p, int n);

int main(void)
{
  unsigned int x = 0b11010111;

  printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(x));
  printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(invert(x, 1, 4)));

  return 0;
}

unsigned int invert(int x, int p, int n)
{
  ++p; // First position is 0

  unsigned int mask1 = ~(~0 << n) << p;
  unsigned int mask2 = ~mask1 & x;

  return mask2 | ~x;
}
