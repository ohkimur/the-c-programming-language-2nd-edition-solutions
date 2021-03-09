#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

int get_token(void);
void decl(void);
void dir_decl(void);

enum
{
  NAME,
  PARENS,
  BRACKETS
};

int token_type;

char token[MAX_TOKEN_LEN];
char name[MAX_TOKEN_LEN];
char data_type[MAX_TOKEN_LEN];
char out[1000];

int main(void)
{
  while (get_token() != EOF)
  {
    strcpy(data_type, token);
    out[0] = '\0';
    decl();
    printf("%s: %s %s\n", name, out, data_type);
  }

  return EXIT_SUCCESS;
}

int get_token(void)
{
  int c;
  char *token_p = token;

  while ((c = getc(stdin)) == ' ' || c == '\t')
    ;

  if (c == '(')
  {
    if ((c = getc(stdin)) == ')')
    {
      strcpy(token, "()");
      return token_type = PARENS;
    }
    ungetc(c, stdin);
    return token_type = '(';
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
    return token_type = BRACKETS;
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
    return token_type = NAME;
  }

  return token_type = c;
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
  if (token_type == '(')
  {
    decl();
    if (token_type != ')')
    {
      puts("ERROR: missing )\n");
    }
  }
  else if (token_type == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    puts("ERROR: expected name or (decl)\n");
  }

  int type;
  while ((type = get_token()) == PARENS || type == BRACKETS)
  {
    if (type == PARENS)
    {
      strcat(out, " function returning");
    }
    else if (type == BRACKETS)
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}
