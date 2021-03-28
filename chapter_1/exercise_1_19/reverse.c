#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int max_line_len);
int length(char line[]);
void reverse(char line[]);

int main(void)
{
  int len;
  char line[MAXLINE];

  while ((len = get_line(line, MAXLINE)) > 0)
  {
    reverse(line);
    printf("%s", line);
  }

  return 0;
}

int get_line(char line[], int max_line_len)
{
  int c, i;

  i = 0;
  while (i < max_line_len - 1 && (c = getchar()) != EOF && c != '\n')
  {
    line[i] = c;
    ++i;
  }

  if (c == '\n')
  {
    line[i] = '\n';
    ++i;
  }

  line[i] = '\0';

  return i;
}

int length(char line[])
{
  int i;

  for (i = 0; line[i] != '\0'; ++i)
    ;

  return i;
}

void reverse(char line[])
{
  int i_front = 0;
  int i_back = length(line);
  char temp;

  i_back -= 2;
  while (i_back > i_front)
  {
    temp = line[i_front];
    line[i_front] = line[i_back];
    line[i_back] = temp;

    ++i_front;
    --i_back;
  }
}
