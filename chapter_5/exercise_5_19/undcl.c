#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100
#define MAX_OUT_LEN 1000

void skip_blanks();
void skip_comments();

void get_name(char *dest, const size_t max_len);
int get_next_token(void);

enum token_type
{
  NAME,
  PARENS,
  BRACKETS,
  PAREN_OPEN = '(',
  PAREN_CLOSE = ')',
  BRACKET_OPEN = '[',
  BRACKET_CLOSE = ']'
};

int next_token;

char token[MAX_TOKEN_LEN];
char out[MAX_OUT_LEN];

int main(void)
{
  char temp[MAX_OUT_LEN + MAX_TOKEN_LEN];

  while (get_next_token() != EOF)
  {
    strcpy(out, token);

    while (get_next_token() != '\n')
    {
      if (next_token == PARENS)
      {
        if (out[0] == '*')
        {
          sprintf(temp, "(%s)", out);
          strcpy(out, temp);
        }

        strcat(out, token);
      }
      else if (next_token == BRACKETS)
      {
        if (out[0] == '*')
        {
          sprintf(temp, "(%s)", out);
          strcpy(out, temp);
        }

        sprintf(temp, "[%s]", token);
        strcat(out, temp);
      }
      else if (next_token == '*')
      {
        sprintf(temp, "*%s", out);
        strcpy(out, temp);
      }
      else if (next_token == NAME)
      {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      }
      else
      {
        printf("Syntax Error: Invalid input at %s.\n", token);
      }
    }
    puts(out);
  }

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
        ungetc('\n', stdin);
        return;
      }
    }
  }
  ungetc(c, stdin);
}

void get_name(char *dest, const size_t max_len)
{
  int c;
  size_t i = 0;
  while ((isalnum(c = getc(stdin)) || c == '_') && i < max_len)
  {
    dest[i++] = c;
  }
  dest[i] = '\0';
  ungetc(c, stdin);
}

int get_next_token(void)
{
  skip_blanks();
  skip_comments();
  skip_blanks();

  int c = getc(stdin);
  if (c == '(')
  {
    skip_blanks();

    c = getc(stdin);
    if (c == ')')
    {
      strcpy(token, "()");
      return next_token = PARENS;
    }
    ungetc(c, stdin);

    return next_token = PAREN_OPEN;
  }
  else if (c == '[')
  {
    skip_blanks();
    get_name(token, MAX_TOKEN_LEN);
    skip_blanks();

    c = getc(stdin);
    if (c == ']')
    {
      return next_token = BRACKETS;
    }
    ungetc(c, stdin);

    return next_token = BRACKET_OPEN;
  }
  else if (isalpha(c))
  {
    ungetc(c, stdin);
    get_name(token, MAX_TOKEN_LEN);
    return next_token = NAME;
  }

  return next_token = c;
}

// NOTE: run: ./undcl < test.txt
