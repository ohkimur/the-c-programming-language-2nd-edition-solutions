#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int max_line_len);
int remove_trailing_blanks(char line[], int length);

int main(void)
{
  int len;
  char line[MAXLINE];

  while ((len = get_line(line, MAXLINE)) > 0)
  {
    len = remove_trailing_blanks(line, len);

    if (len > 1 || line[0] != '\n')
    {
      printf("%s", line);
    }
  }

  return 0;
}

int get_line(char line[], int max_line_len)
{
  int c, i;

  for (i = 0; i < max_line_len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

#define HAS_NEWLINE 1
#define NO_NEWLINE 0

int remove_trailing_blanks(char line[], int length)
{
  int i, has_newline;

  has_newline = NO_NEWLINE;

  for (i = length - 1; i >= 0 && (line[i] == '\n' || line[i] == ' ' || line[i] == '\t'); --i)
  {
    if (line[i] == '\n')
    {
      has_newline = HAS_NEWLINE;
    }
  }

  if (has_newline == HAS_NEWLINE)
  {
    line[i + 1] = '\n';
    line[i + 2] = '\0';
    return i + 2;
  }

  line[i + 1] = '\0';
  return i + 1;
}
