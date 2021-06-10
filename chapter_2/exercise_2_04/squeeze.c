#include <stdio.h>

#define MAXSTR 1000

void squeeze(char str1[], char str2[]);

int main(void)
{
  char str1[MAXSTR] = "abcdefg";
  char str2[MAXSTR] = "abcd";

  squeeze(str1, str2);

  printf("%s", str1);

  return 0;
}

void squeeze(char str1[], char str2[])
{
  int i, j, k;
  for (k = 0; str2[k] != '\0'; ++k)
  {
    for (i = j = 0; str1[i] != '\0'; ++i)
    {
      if (str1[i] != str2[k])
      {
        str1[j++] = str1[i];
      }
    }

    str1[j] = '\0';
  }
}
