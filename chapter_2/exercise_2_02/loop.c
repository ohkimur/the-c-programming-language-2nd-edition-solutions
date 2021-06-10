#include <stdio.h>

#define MAXLINE 1000

int main(void)
{
  char s[MAXLINE];

  // int i;
  // int c;
  // for (i = 0; (i < MAXLINE - 1) * ((c = getchar()) != '\n') * (c != EOF); ++i)
  // {
  //   s[i] = c;
  // }

  int i = 0;
  int loop = 1;
  while (loop)
  {
    char c = getchar();

    if (i >= (MAXLINE - 1))
    {
      loop = 0;
    }
    else if (c == '\n')
    {
      loop = 0;
    }
    else if (c == EOF)
    {
      loop = 0;
    }

    s[i++] = c;
  }

  s[i] = '\0';

  printf("%s", s);

  return 0;
}

// NOTE: The multiplication operation could work in this case because each
// expression is evaluated as a 1 or 0 (true or false), and a multiplication
// between expressions can have the value 1 only if all the expressions are true.
// However, the order of multiplication is not guaranteed to be sequenced as with
// logical operations. So, this is could cause serious problems depending on how
// the compiler deals with multiplication.
