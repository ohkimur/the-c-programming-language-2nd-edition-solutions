#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100
#define MAX_OUT_LEN 1000

int get_next_token(void);
void decl(void);
void dir_decl(void);

enum boolean
{
  FALSE,
  TRUE
};

enum token_type
{
  NAME,
  PAREN_OPEN = '(',
  PAREN_CLOSE = ')',
  PARENS,
  BRACKET_OPEN = '[',
  BRACKET_CLOSE = ']',
  BRACKETS
};

int next_token;

char token[MAX_TOKEN_LEN];
char name[MAX_TOKEN_LEN];
char data_type[MAX_TOKEN_LEN];
char out[MAX_OUT_LEN];

int main(void)
{
  while (get_next_token() != EOF)
  {
    strcpy(data_type, token);
    out[0] = '\0';

    decl();

    if (next_token != '\n')
    {
      puts("ERROR: incorrect syntax.");

      // do
      // {
      //   get_next_token();
      // } while (next_token != '\n' && next_token != EOF);
    }
    else
    {
      printf("%s:\t%s %s\n", name, out, data_type);
    }
  }

  return EXIT_SUCCESS;
}

int get_next_token(void)
{
  int c;
  char *token_p = token;

  while ((c = getc(stdin)) == ' ' || c == '\t')
    ;

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
      while ((c = getc(stdin)) != EOF)
      {
        if (c == '*')
        {
          c = getc(stdin);

          if (c == '/')
          {
            break;
          }
        }
      }
    }

    c = getc(stdin);
  }

  if (c == '(')
  {
    while ((c = getc(stdin)) == ' ' || c == '\t')
      ;

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
    *token_p++ = c;
    while ((*token_p++ = getc(stdin)) != ']')
    {
      if (*(token_p - 1) == ' ' || *(token_p - 1) == '\t')
      {
        --token_p;
      }
    }
    *token_p = '\0';

    return next_token = BRACKETS;
  }
  else if (isalpha(c))
  {
    *token_p++ = c;
    while (isalnum(c = getc(stdin)))
    {
      *token_p++ = c;
    }
    *token_p = '\0';
    ungetc(c, stdin);

    return next_token = NAME;
  }

  return next_token = c;
}

void decl(void)
{
  int nr_of_stars = 0;
  while (get_next_token() == '*')
  {
    ++nr_of_stars;
  }

  dir_decl();

  while (nr_of_stars--)
  {
    strcat(out, " pointer to");
  }
}

void dir_decl(void)
{
  if (next_token == '\n')
  {
    return;
  }

  if (next_token == PAREN_OPEN)
  {
    decl();

    if (next_token != PAREN_CLOSE)
    {
      puts("ERROR: missing )");
    }
  }
  else if (next_token == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    puts("ERROR: expected name or (decl)");
  }

  while ((next_token = get_next_token()) == PARENS || next_token == BRACKETS)
  {
    if (next_token == PARENS)
    {
      strcat(out, " function returning");
    }
    else if (next_token == BRACKETS)
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}
