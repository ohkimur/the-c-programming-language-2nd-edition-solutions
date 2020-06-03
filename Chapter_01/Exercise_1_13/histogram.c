#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define BUFFER 100

void main()
{
  int histogram[BUFFER];
  int in = FALSE;
  int newWord = FALSE;
  int i = 0;

  // Initialize the histogram array with 0
  for(i = 0; i <= BUFFER; ++i)
  {
    histogram[i] = 0;
  }

  // Count the words length and store in histogram array at the
  // specific index
  i = 0;
  int size = 0;
  char c;
  while((c = getchar()) != EOF)
  {
    if(c == ' ' || c == '\t' || c == '\n')
    {
      in = FALSE;

      if(!newWord)
      {
        newWord = TRUE;
        ++histogram[i - 1];

        if(size < i - 1)
        {
          size = i - 1;
        }

        i = 0;
      }
    }
    else
    {
      in = TRUE;
      newWord = FALSE;
      ++i;
    }
  }

  // Add in the histogram array a end of useful data char
  histogram[size + 1] = '$';

  // Print horizontal histogram
  printf("Horizontal Histogram\n--------------------\n");

  i = 0;
  while(histogram[i] != '$')
  {
    printf("%3d: \t", i + 1);

    int j;
    for(j = 0; j < histogram[i]; ++j)
    {
      putchar('#');
    }

    putchar('\n');

    ++i;
  }

  putchar('\n');

  // Print a vertical histogram
  printf("Vertical Histogram\n------------------\n");

  int max = size;
  for(max; max >= 0; --max)
  {
    i = 0;
    while(histogram[i] != '$')
    {
      if(max == 0)
      {
        printf("%2d ", i + 1);
      }
      else if(histogram[i] >= max)
      {
        printf("## ");
      }
      else
      {
        printf("   ");
      }

      ++i;
    }
    
    putchar('\n');
  }

}

// Exercise page: 38

// OBS: An array is a fixed memory space so we can't realloc memory.
// A fixed buffer will be a solution.
// Printing a horizontal histogram is easy, but a vertical histogram 
// needs some special mechanism to print in vertical columns. I used
// the max value from the histogram, and than I iterate multiple times
// trought histogram array decrementing the max value and I checked
// if the histogram[i] >= lastMax to print the "## " chars.
