#include <stdio.h>

int atoi(const char *s);

int main(void)
{
  int i;
  char *s = "12s3a";

  i = atoi(s);

  printf("atoi: %d", i);

  return 0;
}

int atoi(const char *s)
{
  int i = 0;

  while (*s != '\0' && *s > '0' && *s < '9')
  {
    i = i * 10 + *s - '0';
    ++s;
  }

  return i;
}
