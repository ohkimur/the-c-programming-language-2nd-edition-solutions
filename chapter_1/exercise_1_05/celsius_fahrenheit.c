#include <stdio.h>

// Print Celsius-Fahrenheit table
// for celsius = 0, 20, ... 300
// floating point version with for loop

int main(void)
{
  float celsius, fahr;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("Celsius\tFahr\n");
  printf("---------------\n");

  for (celsius = upper; celsius >= lower; celsius = celsius - step)
  {
    fahr = (9.0 / 5.0) * celsius + 32.0f;
    printf("%3.0f\t\t%6.1f\n", celsius, fahr);
  }

  return 0;
}

// NOTE: Sometimes the for loop can be more explicit and more readable then the
// while loop because it's more compact. The initialization and the incrementation
// of the counter variable is done through the for loop params. However, the while
// loop can be, sometimes, more customizable.
