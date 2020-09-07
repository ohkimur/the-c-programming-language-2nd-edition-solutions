#include <stdio.h>

#define MAXLINE 1000

int getln(char line[], int limit);
void remove_trailing_blanks(char line[], int length);

int main(void)
{
  int len;
  char line[MAXLINE];

  while ((len = getln(line, MAXLINE)) > 0)
  {
    remove_trailing_blanks(line, len);
    printf("%s", line);
  }

  return 0;
}

int getln(char line[], int limit)
{
  int c, i;

  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

void remove_trailing_blanks(char line[], int length)
{
  int i;

  for (i = length - 2; line[i] == ' ' || line[i] == '\t'; --i)
    ;

  line[i + 1] = '\n';
  line[i + 2] = '\0';
}

// NOTE: A very simple idea is to create a simple no body for loop that actually
// iterate backwards trough char array and remove trailing blanks, in this case
// spaces and tabs. It is very important to add at the end the newline and the
// end of string special characters.
