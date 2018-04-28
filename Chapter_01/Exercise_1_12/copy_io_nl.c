#include <stdio.h>

#define IN 1
#define OUT 0

#define TRUE 1
#define FALSE 0

main()
{
    int state = OUT;
    int newline = FALSE;
    
    char c;
    while((c = getchar()) != EOF)
    {
        if(c == ' ' || c == '\t' || c == '\n')
        {
            state = OUT;

            if(!newline)
            {
                newline = TRUE;
                putchar('\n');
            }
        }
        else
        {
            state = IN;
            newline = FALSE;
            putchar(c);
        }
    }
}

// Exercise page: 35

// OBS: In this program I recycled the idea of IN/OUT for a word.
// This should be more efficient and easy to read. Also there is a
// need for another flag for newline, which can have the type boolean.
// The idea of TRUE/FALSE can be reused for IN/OUT, so the program
// can be written even more compact, but for the simpliciy I keep
// the recycled idea with IN/OUT and TRUE/FALSE.