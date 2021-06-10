#include <stdio.h>
#include <ctype.h>

#define MAXLEN 500

int get_line(char line[], unsigned int max_line_len);
double atof(char s[]);

int main(void)
{
  char line[MAXLEN];

  get_line(line, MAXLEN);
  printf("%s", line);

  printf("%f", atof(line));

  return 0;
}

int get_line(char line[], unsigned int max_line_len)
{
  int i = 0, c;

  while (i < max_line_len - 1 && (c = getchar()) != '\n')
  {
    line[i] = c;
    ++i;
  }

  if (c == '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}

double atof(char s[])
{
  double val, power;
  int i, sign, exp_sign = 1, exp_pwr = 0;

  for (i = 0; isspace(s[i]); ++i)
    ;

  sign = (s[i] == '-') ? -1 : 1;

  if (s[i] == '+' || s[i] == '-')
  {
    ++i;
  }

  for (val = 0.0; isdigit(s[i]); ++i)
  {
    val = 10.0 * val + (s[i] - '0');
  }

  if (s[i] == '.')
  {
    ++i;
  }

  for (power = 1.0; isdigit(s[i]); ++i)
  {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  if (s[i] == 'e' || s[i] == 'E')
  {
    if (s[++i] == '-')
    {
      exp_sign = -1;
      ++i;
    }
  }

  while (isdigit(s[i]))
  {
    exp_pwr = 10 * exp_pwr + (s[i] - '0');
    ++i;
  }

  while (exp_pwr)
  {
    if (exp_sign == -1)
    {
      power *= 10;
    }
    else
    {
      power /= 10;
    }

    --exp_pwr;
  }

  return sign * val / power;
}
