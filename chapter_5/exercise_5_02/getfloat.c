#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLEN 1000
#define BUFFSIZE 100

int getch(void);
void ungetch(int c);
int getfloat(float *pn);

int main(void)
{
  float number = 0.0;

  getfloat(&number);
  printf("number: %f\n", number);

  return 0;
}

int bufp = 0;
int buf[BUFFSIZE];

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

int getfloat(float *pn)
{
  int c, sign;

  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-')
  {
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;

  if (c == '+' || c == '-')
  {
    if (!isdigit(c = getch()))
    {
      ungetch(c);
      ungetch(sign == 1 ? '+' : '-');
      return 0;
    }
  }

  for (*pn = 0; isdigit(c); c = getch())
  {
    *pn = 10 * *pn + (c - '0');
  }

  if (c == '.')
  {
    int i;
    for (i = 1; (c = getch()) && isdigit(c); ++i)
    {
      *pn += (c - '0') / (pow(10, i));
    }
  }

  *pn = *pn * sign;

  if (c != EOF)
  {
    ungetch(c);
  }

  return c;
}

// NOTE: The getfloat() function should return an integer like getint().
