#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100
#define MAX_OUT_LEN 1000

int get_token(void);
void dcl(void);
void dir_dcl(void);

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

int current_token;

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

    dcl();

    if (current_token != '\n')
    {
      puts("ERROR: incorrect syntax.");

      do
      {
        get_token();
      } while (current_token != '\n' && current_token != EOF);
    }
    else
    {
      printf("%s:%s %s\n", name, out, data_type);
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

  // Ignore comments.
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
      return current_token = PARENS;
    }
    ungetc(c, stdin);

    return current_token = PAREN_OPEN;
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

    return current_token = BRACKETS;
  }
  else if (isalpha(c))
  {
    *token_p++ = c;
    while (isalnum(c = getc(stdin)) || c == '_')
    {
      *token_p++ = c;
    }
    *token_p = '\0';
    ungetc(c, stdin);

    return current_token = NAME;
  }

  return current_token = c;
}

void dcl(void)
{
  int nr_of_stars = 0;
  while (get_token() == '*')
  {
    ++nr_of_stars;
  }

  dir_dcl();

  while (nr_of_stars--)
  {
    strcat(out, " pointer to");
  }
}

void dir_dcl(void)
{
  if (current_token == '\n')
  {
    return;
  }

  if (current_token == PAREN_OPEN)
  {
    dcl();

    if (current_token != PAREN_CLOSE)
    {
      puts("ERROR: missing )");
    }
  }
  else if (current_token == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    puts("ERROR: expected name or (dcl)");
  }

  while ((current_token = get_token()) == PARENS || current_token == BRACKETS)
  {
    if (current_token == PARENS)
    {
      strcat(out, " function returning");
    }
    else if (current_token == BRACKETS)
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}
