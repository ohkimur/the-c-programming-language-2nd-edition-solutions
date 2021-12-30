#include <stdio.h>

#define MAXLEN 100

void int_to_array(int n, char str[]);

int main(void)
{
  int n = -1234;
  char str[MAXLEN];

  int_to_array(n, str);
  printf("%s\n", str);

  n = -7676;

  int_to_array(n, str);
  printf("%s", str);

  return 0;
}

void int_to_array(int n, char str[])
{
  static int i = 0;

  if (n)
  {
    if(n < 0){
      i = 0;
      str[i++] = '-';
      n *= -1;
    }

    int d = n % 10;
    n /= 10;


    int_to_array(n, str);
 

    str[i++] = d + '0';
    str[i] = '\0';
  }
}
