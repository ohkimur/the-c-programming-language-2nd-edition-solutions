#include <stdio.h>

#define MAXSTR 1000

#define IN 1
#define OUT 0

#define TRUE (1 == 1)
#define FALSE !TRUE

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
  int line_nr = 1;

  int parentheses = 0;
  int brackets = 0;
  int braces = 0;

  int single_quotes = 0;
  int double_quotes = 0;

  int block_comment = OUT;
  int line_comment = OUT;

  int i = 0;
  while (str[i] != '\0')
  {
    if (str[i] == '\n')
    {
      ++line_nr;
    }

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

    if (str[i] == '\'' && str[i - 1] != '\\' && !single_quotes && !double_quotes)
    {
      single_quotes = IN;
    }
    else if (str[i] == '\'' && str[i - 1] != '\\')
    {
      single_quotes = OUT;
    }

    if (str[i] == '"' && str[i - 1] != '\\' && !double_quotes && !single_quotes)
    {
      double_quotes = IN;
    }
    else if (str[i] == '"' && str[i - 1] != '\\')
    {
      double_quotes = OUT;
    }

    if (str[i] == '/' && str[i + 1] == '*' && !block_comment)
    {
      block_comment = IN;
    }
    else if (str[i] == '*' && str[i + 1] == '/')
    {
      block_comment = OUT;
    }

    if (str[i] == '/' && str[i + 1] == '/' && !line_comment)
    {
      line_comment = IN;
    }
    else if (str[i] == '\n')
    {
      line_comment = OUT;
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
