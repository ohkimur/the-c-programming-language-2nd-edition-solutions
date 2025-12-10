#include <stdio.h>

#define MAXLINE 1000

int main(void) {
    char s[MAXLINE];
    int c;
    int i = 0;

    // int i;
    // int c;
    // for (i = 0; (i < MAXLINE - 1) * ((c = getchar()) != '\n') * (c != EOF);
    // ++i)
    // {
    //   s[i] = c;
    // }

    while (1) {
        if (i >= MAXLINE - 1) {
            break;
        }

        c = getchar();

        if (c == '\n') {
            break;
        } else if (c == EOF) {
            printf("\n");
            break;
        } else
            s[i++] = c;
    }

    s[i] = '\0';

    printf("%s\n", s);

    return 0;
}

// NOTE: The multiplication operation could work in this case because each
// expression is evaluated as a 1 or 0 (true or false), and a multiplication
// between expressions can have the value 1 only if all the expressions are
// true. However, the order of multiplication is not guaranteed to be sequenced
// as with logical operations. So, this is could cause serious problems
// depending on how the compiler deals with multiplication.
