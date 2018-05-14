#include <stdio.h>

#define MAXLEN 100

void intToArray(int n, char str[]);
typedef enum __BOOL
{
    false,
    true
} bool;

int main(void)
{
    int n = 1234;
    char str[MAXLEN];

    intToArray(n, str);
    printf("->%s<-", str);

    return 0;
}

void intToArray(int n, char str[])
{
    static int i = 0;

    if(n)
    {
        int d = n % 10;
        n /= 10;

        intToArray(n, str);
        
        str[i++] = d + '0';
        str[i] = '\0';
    }
}

// Exercise page: 102

// OBS: Silence is golden.
