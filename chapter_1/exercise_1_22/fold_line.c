#include <stdio.h>

#define MAXLINE 1000
#define TRUE (1 == 1)
#define FALSE !TRUE

int getln(char line[], int limit);
void fold_line(char line[], char fold_str[], int n_break);

int main(void)
{
  char line[MAXLINE];
  char fold_str[MAXLINE];

  getln(line, MAXLINE);

  fold_line(line, fold_str, 30);

  printf("%s", fold_str);

  return 0;
}

int getln(char line[], int limit)
{
  int c, i = 0;

  while (i < limit - 1 && (c = getchar()) != EOF && c != '\n')
  {
    line[i++] = c;
  }

  if (c == '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}

void fold_line(char line[], char fold_str[], int n_break)
{
  int i, j;
  int split = FALSE;
  int offset = 10;

  for (i = 0, j = 0; line[i] != '\0'; ++i, ++j)
  {
    if (i && i % n_break == 0)
    {
      split = TRUE;
    }

    if (split && (line[i] == ' ' || i > n_break + offset))
    {
      fold_str[j++] = '\n';
      split = FALSE;
      ++i;
    }

    fold_str[j] = line[i];
  }

  if (line[i] == '\n')
  {
    fold_str[j++] = line[i];
  }

  fold_str[j] = '\0';
}
