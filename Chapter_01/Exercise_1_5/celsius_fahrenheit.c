#include <stdio.h>

// Print Celsius-Fahrenheit table
// for celsius = 0, 20, ... 300
// floating point version with for loop

main()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    // Printing a heading abouve the table
    printf("Celsius\tFahr\n");
    printf("---------------\n");

    for(celsius = upper; celsius >= lower; celsius = celsius - step)
    {
        fahr = (9.0/5.0) * celsius + 32.0f;
        printf("%3.0f\t\t%6.1f\n", celsius, fahr);
    }
}

// Exercise page: 28

// OBS: Sometimes the for loop can be more explicit and more
// readable than while because is more compact. The initialization
// and the incrementation of a counter variable is done in header
// of the for loop. While loop can be, sometimes, more customizable
// in some ways.