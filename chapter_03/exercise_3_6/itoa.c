#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

int ilen(int a);
void int_to_array(int n, char s[], int padding);
void str_reverse(char str1[], int index, int size);

int main(void)
{
  int n = 1995;
  char number_str[MAXLEN];

  int_to_array(n, number_str, 6);
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

void int_to_array(int n, char s[], int padding)
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
