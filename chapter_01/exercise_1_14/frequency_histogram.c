#include <stdio.h>

#define ALPHA_NR 26
#define NUM_NR 10

int main(void)
{
  int i;
  char chars_freq[ALPHA_NR + NUM_NR];

  // Initialize the chars_freq array with 0
  for (i = 0; i < (ALPHA_NR + NUM_NR); ++i)
  {
    chars_freq[i] = 0;
  }

  // Count characters from the standard input
  char c;
  while ((c = getchar()) != EOF)
  {
    if (c >= 'a' && c <= 'z')
    {
      ++chars_freq[c - 'a'];
    }
    else if (c >= '0' && c <= '9')
    {
      ++chars_freq[c - '0' + ALPHA_NR];
    }
  }

  // Print horizontal histogram
  for (i = 0; i < (ALPHA_NR + NUM_NR); ++i)
  {
    if (i < ALPHA_NR)
    {
      printf("%c: ", 'a' + i);
    }
    else if (i >= ALPHA_NR)
    {
      printf("%c: ", '0' + i - ALPHA_NR);
    }

    int j;
    for (j = 0; j < chars_freq[i]; ++j)
    {
      printf("#");
    }

    putchar('\n');
  }

  return 0;
}
