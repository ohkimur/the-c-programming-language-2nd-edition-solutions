#include <stdio.h>

main()
{
  char c;
  while((c = getchar()) != EOF)
  {
    if(c != ' ' && c != '\t' && c != '\n')
    {
      putchar(c);
    }
    else
    {
      putchar('\n');
    }
  }
}

// Exercise page: 35