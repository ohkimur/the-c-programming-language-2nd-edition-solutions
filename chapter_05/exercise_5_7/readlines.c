#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 // max # of lines to be sorted
#define MAXLEN 1000
#define MAXSTORE 10000 // max # of chars from all lines to be stored

char *lineptr[MAXLINES]; // pointers to text lines

int getln(char line[], int maxline);

int readlines(char *lineptr[], int nlines, char *stored_lines);
void writelines(char *lineptr[], int nlines);

void swap(char *v[], int i, int j);
void quick_sort(char *lineptr[], int left, int right);

int main()
{
  int nlines;                  // # of input lines read
  char stored_lines[MAXSTORE]; // # of chars to be stored for all lines

  if ((nlines = readlines(lineptr, MAXLINES, stored_lines)) >= 0)
  {
    quick_sort(lineptr, 0, nlines - 1);
    printf("-----\n");
    writelines(lineptr, nlines);
    return 0;
  }
  else
  {
    printf("error: input too big to sort\n");
    return 1;
  }
}

int readlines(char *lineptr[], int maxlines, char *stored_lines)
{
  int len;
  int nlines;

  char *p = stored_lines + strlen(stored_lines); // Init p with the first empty position from stored_lines
  char line[MAXLEN];

  nlines = 0;
  while ((len = getln(line, MAXLEN)) > 0)
  {
    // Checking if the current # of lines exceeds the max # of lines that can be stored
    // Also checking if the max # of chars from the stored_lines buffer is not exceeded
    if (nlines >= maxlines || (strlen(stored_lines) + len) > MAXSTORE)
    {
      return -1;
    }
    else
    {
      line[len - 1] = '\0'; // Delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len; // Move p to the next empty position
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
  {
    printf("%s\n", *lineptr++);
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

void quick_sort(char *v[], int left, int right)
{
  int i;
  int last;

  // Do nothing if the array contains less than 2 elements
  if (left >= right)
  {
    return;
  }

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; ++i)
  {
    if (strcmp(v[i], v[left]) < 0)
    {
      swap(v, ++last, i);
    }
  }

  swap(v, left, last);
  quick_sort(v, left, last - 1);
  quick_sort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
