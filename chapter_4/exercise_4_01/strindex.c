#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

int get_line(char line[], int lim);
int strindex(char source[], char pattern[]);

int main(void)
{
  char line[MAXLEN];
  char pattern[MAXLEN] = "example";

  get_line(line, MAXLEN);
  printf("%s\n", line);

  printf("Pattern found at index %d\n", strindex(line, pattern));

  return 0;
}

int get_line(char line[], int lim)
{
  int i = 0, c;

  while (lim > 0 && (c = getchar()) != EOF && c != '\n')
  {
    line[i++] = c;
    --lim;
  }

  if (c == '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}

int strindex(char source[], char pattern[])
{
  int i, j, k;

  printf("line len: %lu\n", strlen(source));

  for (i = strlen(source); i >= 0; --i)
  {
    for (j = i, k = 0; pattern[k] != '\0' && source[j] == pattern[k]; ++j, ++k)
      ;

    if (k > 0 && pattern[k] == '\0')
    {
      return i;
    }
  }

  return -1;
}

// NOTE: It is simple to find the rightmost string pattern in the initial string
// if we search for the pattern by iterating the initial string from the end to
// the begining.
