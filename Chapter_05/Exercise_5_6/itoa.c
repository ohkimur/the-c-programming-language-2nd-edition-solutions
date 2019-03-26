#include <stdio.h>

unsigned int strlength(char *s);
void reverse(char *s);
void itoa(char *s, int n);

int main(void)
{
    int i = 1234;
    char s[100] = "";

    itoa(s, i);

    printf("itoa: %s\n", s);

    return 0;
}

unsigned int strlength(char *s)
{
    int i = 0;

    while(*s++ != '\0')
    {
        ++i;
    }

    return i;
}

void reverse(char *s)
{
    char *t = s + strlength(s) - 1;
    char aux = 0;

    if(*s == '\0')
        return;

    while(s < t)
    {
        aux = *t;
        *t-- = *s;
        *s++ = aux;
    }
}

void itoa(char *s, int n)
{
    char *t = s;

    while(n)
    {
        *(t++) = n % 10 + '0';
        n /= 10;
    }

    *t = '\0';

    reverse(s);
}

// Exercise page: 121

// OBS: Silence is golden.