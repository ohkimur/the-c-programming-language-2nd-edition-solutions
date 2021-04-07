#include <stdio.h>

#define MAXLINE 10000

#define TRUE (1 == 1)
#define FALSE !TRUE

int get_line(char line[], int max_line_len);
void fold_line(char line[], char fold_str[], int n_break);

int main(void)
{
  char line[MAXLINE];
  char fold_str[MAXLINE];

  while ((get_line(line, MAXLINE)) > 0)
  {
    fold_line(line, fold_str, 40);
    printf("%s", fold_str);
  }

  return 0;
}

int get_line(char line[], int max_line_len)
{
  int c, i = 0;

  while (i < max_line_len - 1 && (c = getchar()) != EOF && c != '\n')
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
  int i, j, m;
  int colon = 0;
  int split = FALSE;

  for (i = 0, j = 0; line[i] != '\0'; i++, j++)
  {
    fold_str[j] = line[i];

    if (fold_str[j] == '\n')
    {
      colon = 0;
    }

    colon++;

    if (colon == n_break)
    {
      split = TRUE;
      for (m = j; m >= j - 10 && split; m--)
      {
        if (fold_str[m] == ' ' || fold_str[m] == '\t')
        {
          fold_str[m] = '\n';
          colon = j - m;

          split = FALSE;
        }
      }

      if (split)
      {
        fold_str[j++] = '-';
        fold_str[j] = '\n';

        colon = 0;
      }
    }
  }

  fold_str[j] = '\0';
}
