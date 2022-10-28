#include <stdio.h>

#define IN 1
#define OUT 0

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

    if (c == ' ' || c == '\n' || c == '\t')
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
