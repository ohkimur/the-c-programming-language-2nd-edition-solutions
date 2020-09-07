#include <stdio.h>

#define IN 1
#define OUT 0

// Count lines, words and characters in input

int main(void)
{
  char nl;
  char nw;
  char nc;

  int state;

  nl = nw = nc = 0;
  state = OUT;

  char c;
  while ((c = getchar()) != EOF)
  {
    ++nc;

    if (c == '\n')
    {
      ++nl;
    }
    else if (c == ' ' || c == '\n' || c == '\t')
    {
      state = OUT;
    }
    else if (state == OUT)
    {
      state = IN;
      ++nw;
    }
  }
  
  printf("lines: %d\nwords: %d\ncharacters: %d\n", nl, nw, nc);

  return 0;
}

// NOTE: To test the program it is necessary to write multiple lines, words, and
// of course characters in input. Also it's very nice to use some escape sequence
// such as tabs for example. To identify problems or bugs it's necessary to test
// the isolated contexts like no characters in input or a very long word in input
// or even a huge sequence of white spaces.
