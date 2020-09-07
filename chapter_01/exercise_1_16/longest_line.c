#include <stdio.h>

#define MAXLINE 1000

int getln(char line[], int maxline);
void copy(char from[], char to[]);

int main(void)
{
  int len;
  char line[MAXLINE];

  int maxlen;
  char maxline[MAXLINE];

  maxlen = 0;
  while ((len = getln(line, MAXLINE)) > 0)
  {
    if (maxlen < len)
    {
      maxlen = len;
      copy(line, maxline);
    }

    printf("line_length: %d\n", len);
  }

  if (maxlen > 0)
  {
    printf("%s", maxline);
  }

  return 0;
}

int getln(char line[], int maxline)
{
  int c, i;

  for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

void copy(char from[], char to[])
{
  int i = 0;

  while ((to[i] = from[i]) != '\0')
  {
    ++i;
  }
}


// NOTE: The getline name is a reserved word, because it's available in stdio.h.
