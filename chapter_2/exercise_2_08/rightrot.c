#include <stdio.h>
#include <math.h>

void printbin(unsigned int x);
unsigned int rightrot(unsigned int x, unsigned int n);

int main(void)
{
  unsigned int x = 0b11110101;

  printbin(x);
  printbin(rightrot(x, 5));

  return 0;
}

void printbin(unsigned int x)
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

unsigned int rightrot(unsigned int x, unsigned int n)
{
  unsigned int msb_1 = ~(~(unsigned)0 >> 1);

  int i;
  for (i = 0; i < n; ++i)
  {
    if (x & 1)
    {
      x = (x >> 1) | msb_1;
    }
    else
    {
      x = (x >> 1);
    }
  }

  return x;
}

// NOTE: The rightrot function rotate the entire unsigned int var and if we print
// just a byte we can't see all bits. In order to print all the bits from an
// unsigned int we need to determine the size of an unsigned int, wich is
// machine dependent, and then print 0 or 1 to the output using powers of 2.
