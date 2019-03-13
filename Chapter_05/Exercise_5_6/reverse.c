#include <stdio.h>

unsigned int strlen(char *s);
void reverse(char *s);

int main(void)
{
    char s[100] = "test";

    reverse(s);
    puts(s);  

    return 0;
}

unsigned int strlen(char *s)
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
    char *t = s + strlen(s) - 1;
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

// Exercise page: 121

// OBS: Silence is golden.