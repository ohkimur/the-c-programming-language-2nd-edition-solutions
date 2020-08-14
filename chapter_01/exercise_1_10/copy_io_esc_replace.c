#include <stdio.h>

int main(void)
{
  char c;
  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      putchar('\\');
      putchar('t');
    }
    else if (c == '\b')
    {
      putchar('\\');
      putchar('b');
    }
    else if (c == '\\')
    {
      putchar('\\');
      putchar('\\');
    }
    else
    {
      putchar(c);
    }
  }
  
  return 0;
}

// Exercise page: 34

// NOTE: To print escape to output it is necessary to put each compose
// char from the escape sequence to output.
