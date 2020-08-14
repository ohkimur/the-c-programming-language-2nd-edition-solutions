#include <stdio.h>

int main(void)
{
  char c;
  while ((c = getchar()) != EOF)
  {
    if (c != ' ' && c != '\t' && c != '\n')
    {
      putchar(c);
    }
    else
    {
      putchar('\n');
    }
  }
  
  return 0;
}

// Exercise page: 35
