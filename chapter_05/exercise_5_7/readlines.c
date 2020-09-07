#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
char lines[MAXLINES][MAXLEN];

void swap(char *array[], int i, int j);

size_t get_line(char *s, const int strlen);

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int maxlines);
void qsortlines(char *lineptr[], int left, int right);

int main(int argc, char const *argv[])
{
  int nlines;

  char *lineptr[MAXLINES];

  // Memory allocation in main
  for (size_t i = 0; i < MAXLEN; ++i)
  {
    lineptr[i] = (char *)malloc(MAXLEN * sizeof(char));
  }

  if ((nlines = readlines(lineptr, 3)))
  {
    qsortlines(lineptr, 0, nlines - 1);
    putchar('\n');
    writelines(lineptr, 3);
    return 0;
  }
  else
  {
    puts("error: input too big to sort");
    return 1;
  }

  // Free the allocated memory
  for (size_t i = 0; i < MAXLEN; ++i)
  {
    free(lineptr[i]);
  }

  return 0;
}

size_t get_line(char *s, const int strlen)
{
  size_t i = 0;

  while ((*s = getchar()) != EOF && *s != '\n' && ++i < strlen)
  {
    ++s;
  }

  *s = '\0';

  return i;
}

int readlines(char *lineptr[], int maxlines)
{
  int line_len;
  int nlines;

  char line_temp[MAXLEN];

  nlines = 0;
  while (nlines < maxlines)
  {
    if ((line_len = get_line(line_temp, MAXLEN)))
    {
      // char *line = (char *)malloc(line_len * sizeof(char));
      line_temp[line_len] = '\0'; // Replace \n with \0
      // strcpy(line, line_temp);
      strcpy(lineptr[nlines++], line_temp);
    }
    else
    {
      return -1;
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int maxlines)
{
  int i = 0;

  while (i < maxlines)
  {
    puts(lineptr[i++]);
  }
}

void swap(char *array[], int i, int j)
{
  char *temp;

  temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

void qsortlines(char *lineptr[], int left, int right)
{
  int i;
  int last;

  if (left >= right)
  {
    return;
  }

  swap(lineptr, left, (left + right) / 2);

  last = left;

  for (i = left + 1; i <= right; ++i)
  {
    if (strcmp(lineptr[i], lineptr[left]) < 0)
    {
      swap(lineptr, ++last, i);
    }
  }

  swap(lineptr, left, last);

  qsortlines(lineptr, left, last - 1);
  qsortlines(lineptr, left + 1, last);
}
