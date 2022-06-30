#include <stdio.h>

#define MAXSTR 10000

#define TRUE (1 == 1)
#define FALSE !TRUE

// This is a test comment.

int get_str(char str[], int limit); // This is another test comment.
void remove_comments(char str[], char no_com_str[]);

int main(void)
{
  /**
   * This is multiline
   * block
   * comment.
  */

  char str[MAXSTR];
  char no_com_str[MAXSTR];

  get_str(str, MAXSTR);

  remove_comments(str, no_com_str);

  printf("%s", no_com_str);

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

void remove_comments(char str[], char no_com_str[])
{
  int in_quote = FALSE;
  int line_comment = FALSE;
  int block_comment = FALSE;

  int i = 0, j = 0;
  while (str[i] != '\0')
  {
    if (!block_comment)
    {
      if (!in_quote && str[i] == '"')
    {
      in_quote = TRUE;
    }
    else if (in_quote && str[i] == '"')
    {
      in_quote = FALSE;
    }
    }

    if (!in_quote)
    {
      if (str[i] == '/' && str[i + 1] == '*' && !line_comment)
      {
        block_comment = TRUE;
      }

      if (str[i] == '*' && str[i + 1] == '/')
      {
        block_comment = FALSE;
        i += 2;
      }

      if (str[i] == '/' && str[i + 1] == '/')
      {
        line_comment = TRUE;
      }

      if (str[i] == '\n')
      {
        line_comment = FALSE;
      }

      if (line_comment || block_comment)
      {
        ++i;
      }
      else if (!line_comment || !block_comment)
      {
        no_com_str[j++] = str[i++];
      }
    }
    else
    {
      no_com_str[j++] = str[i++];
    }
  }

  no_com_str[j] = '\0';
}

// NOTE: run: ./c_remove_comments < c_remove_comments.c
