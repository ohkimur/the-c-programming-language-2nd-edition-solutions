#include <stdio.h>

#define MAXLINE 1000

/*
 * K&R Exercise 2-2: Write a loop equivalent to:
 *   for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *       s[i] = c;
 * without using && or ||.
 *
 * Note: Using * instead of && is unsafe because it doesn't short-circuit,
 * causing getchar() to be called even when the buffer is full or EOF is
 * reached.
 */

int main(void) {
    char s[MAXLINE];
    int c;
    int i = 0;

    while (1) {
        if (i >= MAXLINE - 1) {
            break;
        }

        c = getchar();

        if (c == '\n') {
            break;
        } else if (c == EOF) {
            break;
        } else {
            s[i++] = c;
        }
    }

    s[i] = '\0';

    printf("%s\n", s);

    return 0;
}
