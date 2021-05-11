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

int is_valid_qualifier(const char *str);
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
  BRACKET_CLOSE = ']',
  ATTR_SEPARATOR = ','
};

size_t line_nr = 0;
enum boolean Error = FALSE;

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
    "custom_type",
};

int main(void)
{
  while (get_next_token() != EOF)
  {
    if (next_token == '\n')
    {
      ++line_nr;
      continue;
    }

    out[0] = '\0';

    if (is_valid_data_type(token))
    {
      strcpy(data_type, token);
    }
    else
    {
      Error = TRUE;
      printf("Error: invalid data type '%s' on line %zu.\n", token, line_nr);

      do
      {
        get_next_token();
      } while (next_token != '\n' && next_token != EOF);

      ++line_nr;
      continue;
    }

    dcl();

    if (next_token != '\n')
    {
      if (next_token == NAME)
      {
        printf("Syntax Error: '%s' unexpected on line %zu.\n", token, line_nr);
      }
      else
      {
        printf("Syntax Error: '%c' unexpected on line %zu.\n", next_token, line_nr);
      }

      do
      {
        get_next_token();
      } while (next_token != '\n' && next_token != EOF);
    }
    else if (!Error)
    {
      printf("%s:%s %s\n", name, out, data_type);
    }

    Error = FALSE;
    ++line_nr;
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

int is_valid_qualifier(const char *str)
{
  if (strcmp(str, "const") == 0 || strcmp(str, "volatile") == 0)
  {
    return TRUE;
  }
  return FALSE;
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
      Error = TRUE;
      printf("Syntax Error: missing ')' on line %zu.\n", line_nr);
    }
  }
  else if (next_token == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    Error = TRUE;
    printf("Syntax Error: expected name or (dcl) on line %zu.\n", line_nr);
  }

  while ((next_token = get_next_token()) == PARENS || next_token == BRACKETS || next_token == PAREN_OPEN)
  {
    if (next_token == PAREN_OPEN)
    {
      strcat(out, " function expecting");
      attr_dcl();
      strcat(out, " and returning");

      if (next_token != PAREN_CLOSE)
      {
        Error = TRUE;
        printf("Syntax Error: missing ')' on line %zu.\n", line_nr);

        if (next_token == '\n')
        {
          return;
        }
      }
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
    if (next_token == ATTR_SEPARATOR)
    {
      strcat(out, ",");
    }
    else if (next_token == NAME)
    {
      if (is_valid_qualifier(token))
      {
        strcat(out, " ");
        strcat(out, token);
        get_next_token();
      }

      if (is_valid_data_type(token))
      {
        enum boolean is_void_type = FALSE;
        if (strcmp(token, "void") == 0)
        {
          is_void_type = TRUE;
        }

        strcat(out, " ");
        strcat(out, token);

        get_next_token();
        if (next_token == NAME)
        {
          if (is_void_type)
          {
            printf("Error: variable '%s' has incomplete type 'void' on line %zu.\n", token, line_nr);
          }

          strcat(out, " ");
          strcat(out, token);
        }
        else if (next_token == PAREN_CLOSE)
        {
          if (is_void_type)
          {
            return;
          }

          Error = TRUE;
          printf("Syntax Error: missing variable name on line %zu.\n", line_nr);
          return;
        }
        else
        {
          Error = TRUE;
          printf("Syntax Error: '%c' unexpected on line %zu.\n", next_token, line_nr);
        }
      }
      else
      {
        Error = TRUE;
        printf("Syntax Error: '%s' unexpected on line %zu.\n", token, line_nr);
      }
    }
    else
    {
      Error = TRUE;
      printf("Syntax Error: '%c' unexpected on line %zu.\n", next_token, line_nr);
    }
  }
}

// NOTE: run: ./dcl < test.txt
