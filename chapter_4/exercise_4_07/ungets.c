#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
#define BUFFSIZE 1000

int getstr(char line[], int limit);
void ungetstr(char line[]);

int main(void)
{
  char line[MAXLEN];
  char temp[MAXLEN];

  getstr(line, MAXLEN);
  printf("%s", line);

  ungetstr(line);

  getstr(temp, MAXLEN);
  printf("%s", temp);

  return 0;
}

int getch(void);
void ungetch(int c);

int getstr(char line[], int limit)
{
  int i = 0, c;

  while (limit - 1 > 0 && (c = getch()) != EOF && c != '\n')
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

void ungetstr(char line[])
{
  int i = strlen(line);

  while (i)
  {
    ungetch(line[--i]);
  }
}

int bufp = 0;
char buf[BUFFSIZE];

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFFSIZE)
  {
    printf("ungetch: too many characters\n");
  }
  else
  {
    buf[bufp++] = c;
  }
}

// NOTE: The ungetstr() function doesn't need access to buf and bufp. It is enough
// just to use the ungetch() function.
