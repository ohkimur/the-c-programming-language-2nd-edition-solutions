#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

char itoc(int a);
void itob(int n, char s[], int b);
void str_reverse(char str1[], int index, int size);

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

// NOTE: It is simple to convert an integer variable to any base just by taking
// the remainder of the number divided by base and then dividing the initial
// number by base. The result need to be reversed to be correct.
