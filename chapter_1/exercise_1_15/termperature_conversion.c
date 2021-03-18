#include <stdio.h>

float celsius_to_fahrenheit(int celsius);

int main(void)
{
  float celsius, fahr;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 30;

  // Printing a heading abouve the table
  printf("Celsius\t\tFahr.\n");
  printf("----------------------\n");

  celsius = lower;
  while (celsius <= upper)
  {
    fahr = celsius_to_fahrenheit(celsius);
    printf("%3.0f\t\t%6.1f\n", celsius, fahr);
    celsius += step;
  }

  return 0;
}

float celsius_to_fahrenheit(int celsius)
{
  return (9.0 / 5.0) * celsius + 32.0f;
}
