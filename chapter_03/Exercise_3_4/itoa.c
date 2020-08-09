#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

void intToArray(int n, char s[]);

int main()
{
  int n = INT_MIN;
  char number_str[MAXLEN];

  intToArray(n, number_str);
  printf("%s\n", number_str);

  return 0;
}

void intToArray(int n, char s[])
{
  int i, sign;

  sign = n;

  i = 0;
  do
  {
    s[i++] = abs(n % 10) + '0';
  }
  while(n /= 10);

  if(sign < 0)
  {
    s[i++] = '-';
  }

  s[i] = '\0';

  strrev(s);
}

// Exercise page: 78

// OBS: It does not handle the smalles negative number because it does not have 
// a positive equivalent. This means that just using a expression like n = -n is
// not enough for the smallest negative number. If we take the absolute value of
// n % 10 we get the correct value and character.
