#include <stdio.h>

#define MAXSTR 10000

#define TRUE (1 == 1)
#define FALSE !TRUE

int get_str(char str[], int limit);
void check_syntax(char str[]);

int main(void)
{
  char str[MAXSTR];

  get_str(str, MAXSTR);
  check_syntax(str);

  return 0;
}

int get_str(char str[], int limit)
{
  int c, i = 0;

  while (i < limit - 1 && (c = getchar()) != EOF)
  {
    str[i++] = c;
  }
  str[i] = '\0';

  return i;
}

void check_syntax(char str[])
{
  int parentheses = 0;
  int brackets = 0;
  int braces = 0;

  int single_quotes = FALSE;
  int double_quotes = FALSE;

  int block_comment = FALSE;
  int line_comment = FALSE;

  int i = 0;
  while (str[i] != '\0' && parentheses >= 0 && brackets >= 0 && braces >= 0)
  {
    if (!line_comment && !block_comment && !single_quotes && !double_quotes)
    {
      if (str[i] == '(')
      {
        ++parentheses;
      }
      else if (str[i] == ')')
      {
        --parentheses;
      }

      if (str[i] == '[')
      {
        ++brackets;
      }
      else if (str[i] == ']')
      {
        --brackets;
      }

      if (str[i] == '{')
      {
        ++braces;
      }
      else if (str[i] == '}')
      {
        --braces;
      }
    }

    if (!line_comment && !block_comment)
    {
      if (str[i] == '\'' && !single_quotes && !double_quotes)
      {
        single_quotes = TRUE;
      }
      else if (single_quotes && str[i] == '\'' && (str[i - 1] != '\\' || str[i - 2] == '\\'))
      {
        single_quotes = FALSE;
      }

      if (str[i] == '"' && !single_quotes && !double_quotes)
      {
        double_quotes = TRUE;
      }
      else if (double_quotes && str[i] == '"' && (str[i - 1] != '\\' || str[i - 2] == '\\'))
      {
        double_quotes = FALSE;
      }
    }

    if (!single_quotes && !double_quotes)
    {
      if (str[i] == '/' && str[i + 1] == '*' && !line_comment)
      {
        block_comment = TRUE;
      }
      else if (str[i] == '*' && str[i + 1] == '/')
      {
        block_comment = FALSE;
      }

      if (str[i] == '/' && str[i + 1] == '/' && !block_comment)
      {
        line_comment = TRUE;
      }
      else if (str[i] == '\n')
      {
        line_comment = FALSE;
      }
    }

    ++i;
  }

  if (parentheses)
  {
    printf("Error: unbalanced parentheses.\n");
  }

  if (brackets)
  {
    printf("Error: unbalanced brackets.\n");
  }

  if (braces)
  {
    printf("Error: unbalanced braces.\n");
  }

  if (single_quotes)
  {
    printf("Error: unbalanced single quotes.\n");
  }

  if (double_quotes)
  {
    printf("Error: unbalanced double quotes.\n");
  }

  if (block_comment)
  {
    printf("Error: block comment not closed.\n");
  }
}
