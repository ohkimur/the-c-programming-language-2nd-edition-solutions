#include <stdio.h>

// Print Fahrenheit-Celsius table
// for fahr = 0, 20, ... 300
// floating point version

int main(void)
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  // Printing a heading above the table
  printf("Fahr\tCelsius\n");
  printf("---------------\n");

  fahr = lower;
  while (fahr <= upper)
  {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f\t\t%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }

  return 0;
}

// NOTE: If all operands from an operation are integers then a integer operation
// is performed. If at least one operand is a floating point number then a
// floating point operation will be performed.
