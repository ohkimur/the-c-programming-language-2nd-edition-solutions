#include <stdio.h>
#include <math.h>

void printbits(unsigned int x);
int bitcount(unsigned int x);

int main(void)
{
  unsigned int x = 0b011010;

  printbits(x);
  printf("x have %d bits of 1.\n", bitcount(x));

  return 0;
}

void printbits(unsigned int x)
{
  unsigned int n = sizeof(unsigned int);

  printf("0b");

  int i;
  for (i = n * 8 - 1; i >= 0; --i)
  {
    (x & (unsigned int)pow(2, i)) ? putchar('1') : putchar('0');
  }

  putchar('\n');
}

int bitcount(unsigned int x)
{
  int b = 0;

  while (x)
  {
    x &= (x - 1);
    ++b;
  }

  return b;
}

// NOTE: The expression x &= (x - 1) deletes the rightmost 1-bit of x because
// x is decremented by 1 and masked with the initial x. If decremented x has
// the rightmost bit 1, shifted to right by logic & operation, it is deleted.
