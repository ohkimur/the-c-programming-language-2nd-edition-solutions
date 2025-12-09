#include <stdio.h>

// Using (void) instead of () explicitly declares that main takes no parameters
// This is the preferred modern C style and avoids compiler warnings
int main(void) {
    int character;
    int previous_character = EOF;

    while ((character = getchar()) != EOF) {
        if (character == ' ' || character == '\t' || character == '\n') {
            if (previous_character != ' ' && previous_character != '\t' &&
                previous_character != '\n') {
                putchar('\n');
            }
        } else {
            putchar(character);
        }

        previous_character = character;
    }

    return 0;
}
