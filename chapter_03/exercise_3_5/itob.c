#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

char itoc(int a);
void itob(int n, char s[], int b);

int main(void)
{
  char s[MAXLEN];

  int n = -2;

  itob(n, s, 16);

  printf("%s", s);

  return 0;
}

char itoc(int a)
{
  if (a <= 9)
  {
    return a + '0';
  }

  return a + 'a' - 10;
}

void itob(int n, char s[], int b)
{
  int i = 0, sign = n;

  do
  {
    s[i++] = itoc(abs(n) % b);
    n /= b;
  } while (n /= b);

  switch (b)
  {
  case 2:
    s[i++] = 'b';
    s[i++] = '0';
    break;

  case 16:
    s[i++] = 'x';
    s[i++] = '0';
    break;
  }

  if (sign < 0)
  {
    s[i++] = '-';
  }

  s[i] = '\0';

  strrev(s);
}

// Exercise page: 78

// NOTE: It is simple to convert an integer variable to any base just by taking
// the remainder of the number divided by base and than dividing the initial
// number by base. The result need to be reversed to be correct.
