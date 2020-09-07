#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8

int getln(char line[], int limit);
void copy(char destination[], char source[]);
void entab(char line[]);

int main(void)
{
  char line[MAXLINE];

  getln(line, MAXLINE);
  printf("%s", line);

  entab(line);
  // printf("%s", line);

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

void copy(char destination[], char source[])
{
  int i = 0;
  while (source[i] != '\0')
  {
    destination[i] = source[i];
    ++i;
  }

  if (source[i] == '\0')
  {
    destination[i] = '\0';
  }
}

void entab(char line[])
{
  int i = 0, k = 0, j = 0;
  char temp[MAXLINE];

  while (line[i] != '\0')
  {
    if (line[i] != ' ')
    {
      temp[j++] = line[i++];
    }
    else
    {
      temp[j++] = ' ';
      ++i;
    }

    if (i % TABSTOP == 0)
    {
      k = j - 1;
      while (temp[k] == ' ')
      {
        --k;
      }

      if (k < j - 1)
      {
        j = k + 1;
        temp[j++] = '\t';
      }
    }
  }

  temp[j] = '\0';

  copy(line, temp);
}


// NOTE: To keep the same tab indentation for every tablength would be more
// apropriate to use a \t every time to reach the next tab indentation.
