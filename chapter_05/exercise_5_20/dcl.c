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

int is_valid_data_type(const char *str);

void dcl(void);
void dir_dcl(void);
void attr_dcl(void);

enum boolean
{
  FALSE,
  TRUE
};

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
char name[MAX_TOKEN_LEN];
char data_type[MAX_TOKEN_LEN];
char out[MAX_OUT_LEN];

char *data_types[] = {
    "void",
    "char",
    "short",
    "int",
    "long",
    "float",
    "double",
};

int main(void)
{
  char *type = "float";
  if (is_valid_data_type(type))
  {
    puts("yes it is!");
  }

  while (get_next_token() != EOF)
  {
    if (next_token == '\n')
    {
      continue;
    }

    strcpy(data_type, token);
    out[0] = '\0';

    dcl();

    if (next_token != '\n')
    {
      if (next_token == NAME)
      {
        printf("ERROR: Syntax error: '%s' unexpected.\n", token);
      }
      else
      {
        printf("ERROR: Syntax error: '%c' unexpected.\n", next_token);
      }

      do
      {
        get_next_token();
      } while (next_token != '\n' && next_token != EOF);
    }
    else
    {
      printf("%s:%s %s\n", name, out, data_type);
    }
  }

  return EXIT_SUCCESS;
}

void skip_blanks()
{
  int c;
  while ((c = getc(stdin)) == ' ' || c == '\t')
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

int is_valid_data_type(const char *str)
{
  size_t nr_of_types = sizeof(data_types) / sizeof(data_types[0]);
  for (size_t i = 0; i < nr_of_types; ++i)
  {
    if (strcmp(data_types[i], str) == 0)
    {
      return TRUE;
    }
  }
  return FALSE;
}

void dcl(void)
{
  int nr_of_stars = 0;
  while (get_next_token() == '*')
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
  if (next_token == PAREN_OPEN)
  {
    dcl();

    if (next_token != PAREN_CLOSE)
    {
      return;
    }
  }
  else if (next_token == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    return;
  }

  while ((next_token = get_next_token()) == PARENS || next_token == BRACKETS || next_token == PAREN_OPEN)
  {
    if (next_token == PAREN_OPEN)
    {
      strcat(out, " function expecting");
      attr_dcl();

      if (next_token != PAREN_CLOSE)
      {
        return;
      }

      strcat(out, " and returning");
    }
    else if (next_token == PARENS)
    {
      strcat(out, " function returning");
    }
    else if (next_token == BRACKETS)
    {
      strcat(out, " array[");
      strcat(out, token);
      strcat(out, "] of");
    }
  }
}

void attr_dcl(void)
{
  while (get_next_token() != PAREN_CLOSE && next_token != '\n')
  {
    if (next_token == ',')
    {
      strcat(out, ",");
    }
    else if (next_token == NAME)
    {
      if (is_valid_data_type(token))
      {
        strcat(out, " ");
        strcat(out, token);

        get_next_token();
        if (next_token == NAME)
        {
          strcat(out, " ");
          strcat(out, token);
        }
      }
      else
      {
        return;
      }
    }
    else
    {
      return;
    }
  }
}

// NOTE: run: ./dcl < test.txt
