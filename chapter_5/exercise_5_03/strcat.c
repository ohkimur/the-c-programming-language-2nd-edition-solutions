#include <stdio.h>

void strcat_ptr(char *s, char *t);

int main(void) {
    char s[100] = "This is the first string";
    char t[] = ", this second string!";

    strcat_ptr(s, t);

    puts(s);

    return 0;
}

// Concatenate t to end of s; s must be big enough.
void strcat_ptr(char *s, char *t) {
    // Find the end of s
    while (*s)
        ++s;

    // copy t to the end of s
    // Extra parentheses around assignment suppress compiler warning about
    // using assignment as condition (this is intentional and safe here)
    while ((*s++ = *t++))
        ;
}
