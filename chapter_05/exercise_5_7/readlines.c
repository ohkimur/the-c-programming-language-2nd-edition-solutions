#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNLINES 5000 // max # of lines to be sorted
#define MAXLEN 1000

char *lineptr[MAXNLINES]; // pointers to text lines

int getln(char line[], int maxline);

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

// void qsort(char *lineptr[], int left, int right);

int main()
{
  int nlines; // # of input lines read

  if ((nlines = readlines(lineptr, MAXNLINES)) >= 0)
  {
    // qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  }
  else
  {
    printf("error: input too big to sort\n");
    return 1;
  }
}

int readlines(char *lineptr[], int maxlines)
{
  int len;
  int nlines;

  char *p;
  char line[MAXLEN];

  nlines = 0;
  while ((len = getln(line, MAXLEN)) > 0)
  {
    if (nlines >= maxlines || (p = malloc(sizeof(char) * len)) == NULL)
    {
      return -1;
    }
    else
    {
      line[len - 1] = '\0'; // delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; ++i)
  {
    printf("%s\n", lineptr[i]);
  }
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
