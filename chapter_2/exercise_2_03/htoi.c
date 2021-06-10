#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXLINE 100

int get_line(char line[], int lim);
int htoi(char hex[]);

int main(void)
{
  char hex[MAXLINE];

  get_line(hex, MAXLINE);

  printf("%d", htoi(hex));

  return 0;
}

int get_line(char line[], int lim)
{
  char c;
  int i = 0;
  while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}

int htoi(char hex[])
{
  int result = 0;

  int i = 0, len = strlen(hex);

  while (i < len)
  {
    if (hex[i] == '0' && (hex[i + 1] == 'x' || hex[i + 1] == 'X'))
    {
      i += 2;
    }

    int temp = tolower(hex[i]);

    if (isdigit(temp))
    {
      temp -= 48;
    }

    if (isalpha(temp) && temp <= 'f')
    {
      temp = temp - 'a' + 10;
    }

    if ((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'a' && hex[i] <= 'f') || (hex[i] >= 'A' && hex[i] <= 'F'))
    {
      result += temp * (int)pow(16, len - i - 1);
    }
    else
    {
      printf("Error: Not a valid hex value.\n Try this format: 0xHHHH, where H is a hex digit.\n");
    }

    ++i;
  }

  return result;
}

// NOTE: The conversion algorithm from hex to dec is very similar with the
// conversion algorithm from bin to dec, but the base is not 2 but 16.
// The general formula is: x1*B^N + x2*B^(N - 1) + ... + xn*B^(N - N), where B
// is the base from we convert to dec, in this case B = 16.
