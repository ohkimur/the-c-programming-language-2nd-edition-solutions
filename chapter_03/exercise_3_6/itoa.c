#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

int ilen(int a);
void intToArray(int n, char s[], int padding);

int main(void)
{
  int n = 1995;
  char number_str[MAXLEN];

  intToArray(n, number_str, 6);
  printf("%s\n", number_str);

  return 0;
}

int ilen(int a)
{
  int i = 0;

  do
  {
    ++i;
  } while (a /= 10);

  return i;
}

void intToArray(int n, char s[], int padding)
{
  int i = 0, sign = n;

  do
  {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10);

  if (sign < 0)
  {
    s[i++] = '-';
  }

  int len = ilen(sign);
  while (len < padding)
  {
    s[i++] = ' ';
    --padding;
  }

  s[i] = '\0';

  strrev(s);
}

// Exercise page: 78

// NOTE: Silence is golden.
