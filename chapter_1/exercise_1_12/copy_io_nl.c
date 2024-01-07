#include <stdio.h>

int main()
{
  int character;
  int previous_character = EOF;

  while ((character = getchar()) != EOF) {
    if (character == ' ' || character == '\t' || character == '\n') {
      if (previous_character != ' ' && previous_character != '\t' && previous_character != '\n') {
        putchar('\n');
      }
    }
    else {
      putchar(character);
    }

    previous_character = character;
  }

  return 0;
}
