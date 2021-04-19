#include <stdio.h>

#define TAB_LENGTH 8

int main(void)
{
  int c;
  unsigned int line_pos = 0;
  unsigned int nr_of_spaces = 0;

  while ((c = getchar()) != EOF)
  {
    ++line_pos;

    if (c == ' ')
    {
      ++nr_of_spaces;

      if (line_pos % TAB_LENGTH == 0 && nr_of_spaces > 1)
      {
        putchar('\t');
        nr_of_spaces = 0;
      }
    }
    else
    {
      while (nr_of_spaces)
      {
        putchar(' ');
        --nr_of_spaces;
      }

      if (c == '\n')
      {
        line_pos = 0;
      }

      putchar(c);
    }
  }

  return 0;
}

// NOTE: run: ./entab < file_in.txt > file_out.txt
