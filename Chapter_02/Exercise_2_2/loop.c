#include <stdio.h>

#define MAXLINE 1000

int main()
{
    char s[MAXLINE];

    int i;
    char c;
    for(i = 0; (i < MAXLINE - 1) * ((c = getchar()) != '\n') * (c != EOF); ++i)
    {
        s[i] = c;
    }

    s[i] = '\0';

    printf("%s", s);

    return 0;
}

// Exercise page: 56

// OBS: The multiplication operation can work in this case because each
// expression is evaluated as a 1 or 0 (true or false), and a multiplication
// between expressions can have the value 1 only if all the expressions are true.