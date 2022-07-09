#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

void int_to_array(int n, char s[]);
void str_reverse(char str1[], int index, int size);

int main(void)
{
  int n = 785;
  char number_str[MAXLEN];

  int_to_array(n, number_str);
  printf("%s\n", number_str);

  return 0;
}

void int_to_array(int n, char s[])
{
  int i, sign;

  sign = n;

  i = 0;
  do
  {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10);

  if (sign < 0)
  {
    s[i++] = '-';
  }

  s[i] = '\0';

  int s_len = strlen(s);
  str_reverse(s, 0, s_len - 1);
}

void str_reverse(char str1[], int index, int size)
{
  char temp;

  temp = str1[index];
  str1[index] = str1[size - index];
  str1[size - index] = temp;

  if (index == size / 2)
  {
    return;
  }

  str_reverse(str1, index + 1, size);
}

// NOTE: It does not handle the smallest negative number because it does not have
// a positive equivalent. This means that just using a expression like n = -n is
// not enough for the smallest negative number. If we take the absolute value of
// n % 10 we get the correct value and character.
