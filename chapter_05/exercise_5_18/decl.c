#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100
#define MAX_OUT_LEN 1000

int get_token(void);
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

int token_error = FALSE;
int global_token_type;

char token[MAX_TOKEN_LEN];
char name[MAX_TOKEN_LEN];
char data_type[MAX_TOKEN_LEN];
char out[MAX_OUT_LEN];

int main(void)
{
  while (get_token() != EOF)
  {
    strcpy(data_type, token);
    out[0] = '\0';

    decl();

    if (global_token_type != '\n')
    {
      puts("ERROR: incorrect syntax.");

      do
      {
        get_token();
      } while (global_token_type != '\n');
    }
    else
    {
      printf("%s:\t%s %s\n", name, out, data_type);
    }
  }

  return EXIT_SUCCESS;
}

int get_token(void)
{
  int c;
  char *token_p = token;

  while ((c = getc(stdin)) == ' ' || c == '\t')
    ;

  if (c == PAREN_OPEN)
  {
    while ((c = getc(stdin)) == ' ' || c == '\t')
      ;

    if (c == PAREN_CLOSE)
    {
      strcpy(token, "()");
      return global_token_type = PARENS;
    }
    ungetc(c, stdin);

    return global_token_type = PAREN_OPEN;
  }
  else if (c == BRACKET_OPEN)
  {
    *token_p++ = c;
    while ((*token_p++ = getc(stdin)) != BRACKET_CLOSE)
    {
      if (*(token_p - 1) == ' ' || *(token_p - 1) == '\t')
      {
        --token_p;
      }
    }
    *token_p = '\0';
    return global_token_type = BRACKETS;
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
    return global_token_type = NAME;
  }

  return global_token_type = c;
}

void decl(void)
{
  int nr_of_stars = 0;
  while (get_token() == '*')
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
  if (global_token_type == PAREN_OPEN)
  {
    decl();
    if (global_token_type != PAREN_CLOSE)
    {
      puts("ERROR: missing )");
    }
  }
  else if (global_token_type == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    puts("ERROR: expected name or (decl)");
  }

  while ((global_token_type = get_token()) == PARENS || global_token_type == BRACKETS)
  {
    if (global_token_type == PARENS)
    {
      strcat(out, " function returning");
    }
    else if (global_token_type == BRACKETS)
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}
