#include <stdio.h>

#define TAB_LENGTH 8

int main(void)
{
  FILE *input;
  char input_name[100];
  printf("Enter the name of the input file : ");
  scanf("%s", input_name);
  printf("\nThe output :\n");
  input = fopen(input_name, "r");
  
  int c;
  unsigned int nr_of_spaces;

  while ((c = getc(input)) != EOF)
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
  fclose(input);

  return 0;
}

/* NOTE: The open the folder in which the input file is present
         using 'cd' in terminal
         Then type the name of the input file
         The output will be printed on the screen.
*/

