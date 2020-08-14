#include <stdio.h>

char lower(char c);

int main(void)
{
  char a = 'A';

  putchar(lower(a));

  return 0;
}

char lower(char c)
{
  return (c >= 'A' && c <= 'Z') ? c += 'a' - 'A' : c;
}

// Exercise page: 66

// NOTE: The ternary operator ?: can be used direct in return.
