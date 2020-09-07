#include <stdio.h>

#define MAXLINE 1000
#define LIMIT 80

int getln(char line[], int limit);

int main(void)
{
  int len;
  char line[MAXLINE];

  while ((len = getln(line, MAXLINE)) > 0)
  {
    if (len > LIMIT)
    {
      printf("%s", line);
    }
  }

  return 0;
}

int getln(char line[], int limit)
{
  int c, i;

  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
  {
    line[i] = c;
  }

  if (c == '\n')
  {
    line[i] = c;
    ++i;
  }

  line[i] = '\0';

  return i;
}

