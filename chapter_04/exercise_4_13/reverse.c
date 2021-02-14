#include <stdio.h>

#define MAXLEN 100

void reverse(char str[]);

int main(void)
{
  char str[MAXLEN] = "This is just a string";

  printf("%s\n", str);
  reverse(str);
  printf("%s\n", str);

  return 0;
}

void reverse(char str[])
{
  static int i = 0;
  static int j = 0;

  if (str[i] != '\0')
  {
    char c = str[i++];
    reverse(str);

    str[j++] = c;
  }
}

// NOTE: As a simple observation when recursive functions are used, static
// variables become handy to construct some useful functionalities.
