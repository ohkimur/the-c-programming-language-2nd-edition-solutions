#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

int getstr(char line[], int limit);
void expand(char src[], char dest[]);

int main(void)
{
  char line[MAXLEN];
  char expanded_ln[MAXLEN];

  getstr(line, MAXLEN);
  printf("%s", line);

  expand(line, expanded_ln);
  printf("%s", expanded_ln);

  return 0;
}

int getstr(char line[], int limit)
{
  int i = 0, c;
  while ((i < limit - 1) && (c = getchar()) != EOF)
  {
    line[i] = c;
    ++i;
  }

  if (c == '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}

void expand(char src[], char dest[])
{
  int i, j = 0;
  for (i = 0; src[i] != EOF; ++i)
  {
    if (src[i + 1] == '-' && src[i] < src[i + 2])
    {
      int k;
      for (k = 0; k <= (src[i + 2] - src[i]); ++k)
      {
        int temp = src[i] + k;
        if ((dest[j - 1] != temp && isdigit(temp)) || isalpha(temp))
        {
          dest[j++] = src[i] + k;
        }
      }

      i += 2;
    }
    else
    {
      dest[j++] = src[i];
    }
  }

  if (src[i] == '\n')
  {
    dest[j++] = src[i];
  }

  dest[j] = '\0';
}


// NOTE: To simply test if a char is a digit or an alpha we can use isdigit() and
// isalpha() wich are located in <ctype.h>
