#include <stdio.h>

main()
{
    char c;
    char last_c;
    while((c = getchar()) != EOF)
    {
        // Solution 1
        // if(c != ' ')
        // {
        //     putchar(c);
        // }
        // else if(last_c != ' ')
        // {
        //     putchar(c);
        // }

        // Solution 2
        // if(!(c == ' ' && last_c == ' '))
        // {
        //     putchar(c);
        // }

        // Solution 3
        if(c != ' ' || last_c != ' ')
        {
            putchar(c);
        }

        last_c = c;
    }
}

// Exercise page: 34

// OBS: Solution 3 is the most elegant, because is fast and compact.