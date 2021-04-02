#include <stdio.h>

#define MAXSTR 10000

#define IN 1
#define OUT 0

int getstr(char str[], int limit);
void check_syntax(char str[]);

int main(void)
{
  char str[MAXSTR];

  getstr(str, MAXSTR);
  check_syntax(str);

  return 0;
}

int getstr(char str[], int limit)
{
  int c, i = 0;

  while (i < limit - 1 && (c = getchar()) != EOF)
  {
    str[i++] = c;
  }

  if (c == '\n')
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

  int single_quotes = OUT;
  int double_quotes = OUT;

  int block_comment = OUT;
  int line_comment = OUT;

  int i = 0;
  while (str[i] != '\0')
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
        single_quotes = IN;
      }
      else if (single_quotes && str[i] == '\'' && (str[i - 1] != '\\' || str[i - 2] == '\\'))
      {
        single_quotes = OUT;
      }

      if (str[i] == '"' && !single_quotes && !double_quotes)
      {
        double_quotes = IN;
      }
      else if (double_quotes && str[i] == '"' && (str[i - 1] != '\\' || str[i - 2] == '\\'))
      {
        double_quotes = OUT;
      }
    }

    if (!single_quotes && !double_quotes)
    {
      if (str[i] == '/' && str[i + 1] == '*' && !line_comment)
      {
        block_comment = IN;
      }
      else if (str[i] == '*' && str[i + 1] == '/')
      {
        block_comment = OUT;
      }

      if (str[i] == '/' && str[i + 1] == '/' && !block_comment)
      {
        line_comment = IN;
      }
      else if (str[i] == '\n')
      {
        line_comment = OUT;
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
