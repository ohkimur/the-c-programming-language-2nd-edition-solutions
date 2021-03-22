#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void skip_blanks();
void skip_comments();
void skip_string_between(char start, char end);
void skip_string_constant();

int get_word(char *word, int max_word_len);

int main(void)
{
  // TODO: Start from here.
  return EXIT_SUCCESS;
}

void skip_blanks()
{
  int c;
  while (isblank(c = getc(stdin)))
    ;
  ungetc(c, stdin);
}

void skip_comments()
{
  int c = getc(stdin);
  if (c == '/')
  {
    c = getc(stdin);
    if (c == '/')
    {
      while ((c = getc(stdin)) != '\n' && c != EOF)
        ;
    }
    else if (c == '*')
    {
      while ((c = getc(stdin)) != '*' && c != EOF)
        ;
      c = getc(stdin);
      if (c == '/')
      {
        return;
      }
    }
  }
  ungetc(c, stdin);
}

void skip_string_between(char start, char end)
{
  int c = getc(stdin);
  if (c == start)
  {
    while ((c = getc(stdin)) != end && c != EOF)
      ;
  }

  if (c != start && c != end)
  {
    ungetc(c, stdin);
  }
}

void skip_string_constant()
{
  skip_string_between('\'', '\'');
  skip_string_between('"', '"');
}

int get_word(char *word, int max_word_len)
{
  skip_blanks();
  skip_comments();
  skip_string_constant();

  int c = getc(stdin);
  size_t i = 0;

  if (c != EOF)
  {
    word[i++] = c;
  }

  if (!isalpha(c))
  {
    word[i] = '\0';
    return c;
  }

  while ((isalnum(c = getc(stdin)) || c == '_') && i < max_word_len)
  {
    word[i++] = c;
  }
  word[i] = '\0';

  return word[0];
}
