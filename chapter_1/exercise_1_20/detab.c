#include <stdio.h>

#define TAB_LENGTH 8

int main(void)
{
  int c;
  unsigned int nr_of_spaces;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      nr_of_spaces = TAB_LENGTH;

      while (nr_of_spaces)
      {
        putchar(' ');
        --nr_of_spaces;
      }
    }
    else
    {
      putchar(c);
    }
  }

  return 0;
}

// NOTE: In UNIX like systems you can execute commands like this:
// ./detab < file_in.txt > file_out.txt that takes the input from a
// file and after the program processed its content puts it to another file.
