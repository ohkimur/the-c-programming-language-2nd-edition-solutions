#include <stdio.h>

#define MAXLINE 1000
#define TABWIDTH 8

int getln(char line[], int limit);
void detab(char line[], char tline[]);

int main(void)
{
  char line[MAXLINE];
  char tline[MAXLINE];

  getln(line, MAXLINE);

  detab(line, tline);

  printf("%s", tline);

  return 0;
}

int getln(char line[], int limit)
{
  int c, i;

  i = 0;
  while (i < limit - 1 && (c = getchar()) != EOF && c != '\n')
  {
    line[i++] = c;
  }

  if (c == '\n')
  {
    line[i++] = '\n';
  }

  line[i] = '\0';

  return i;
}

void detab(char line[], char tline[])
{
  int i = 0, j = 0;
  int spacew = 0;

  while (line[i] != '\0')
  {
    spacew = TABWIDTH - j % TABWIDTH;

    if (line[i] == '\t')
    {
      printf("spacew: %d\n", spacew);

      while (spacew-- > 0)
      {
        tline[j++] = '-';
      }

      ++i;
    }
    else
    {
      tline[j++] = line[i++];
    }
  }

  if (line[i] == '\n')
  {
    tline[j++] = line[i];
  }

  tline[j] = '\0';
}

