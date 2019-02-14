#include <stdio.h>

unsigned int strlen(char *s);
void strcat_ptr(char *s, char *t, unsigned int n);

int main(void)
{
    char s[100] = "This is the first string";
    char *t = ", this second string!";
    unsigned int nr_chars = 5;

    strcat_ptr(s, t, nr_chars);

    puts(s);

    return 0;
}

// Returns the length of the string.
unsigned int strlen(char *s)
{
    unsigned int str_length = 0;

    while((*++s) != '\0')
        ++str_length;

    return str_length;
}

// Concatenate t to end of s; s must be big enough.
void strcat_ptr(char *s, char *t, unsigned int n)
{
    // Find the end of s
    unsigned int s_length = strlen(s);

    // Move the s pointer to the end of the s string.
    s += s_length;

    // copy t to the end of s
    while((*s++ = *t++) != '\0' && n--)
        ;
}

// Exercise page: 121

// OBS: Silence is golden.