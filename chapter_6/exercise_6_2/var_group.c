#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

struct tree_node
{
  char *word;
  int count;
  struct tree_node *left;
  struct tree_node *right;
};

struct tree_node *add_to_tree(struct tree_node *node_p, char *word);
void print_tree(struct tree_node *node_p);

void skip_blanks();
void skip_comments();
void skip_string_between(char start, char end);
void skip_string_constant();

int get_word(char *word, int max_word_len);

int main(void)
{
  struct tree_node *root = NULL;
  char word[MAX_WORD_LEN];

  while (get_word(word, MAX_WORD_LEN) != EOF)
  {
    if (isalpha(word[0]))
    {
      root = add_to_tree(root, word);
    }
  }

  print_tree(root);

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
        return;
      }
    }
  }
  ungetc(c, stdin);
}

void skip_string_between(char start, char end)
{
  int c = getc(stdin);
  if (c == start)
  {
    while ((c = getc(stdin)) != end && c != EOF)
      ;
  }

  if (c != start && c != end)
  {
    ungetc(c, stdin);
  }
}

void skip_string_constant()
{
  skip_string_between('\'', '\'');
  skip_string_between('"', '"');
}

int get_word(char *word, int max_word_len)
{
  skip_blanks();
  skip_comments();
  skip_string_constant();

  int c = getc(stdin);
  size_t i = 0;

  if (c != EOF)
  {
    word[i++] = c;
  }

  if (!isalpha(c))
  {
    word[i] = '\0';
    return c;
  }

  while ((isalnum(c = getc(stdin)) || c == '_') && i < max_word_len)
  {
    word[i++] = c;
  }
  word[i] = '\0';

  return word[0];
}

struct tree_node *add_to_tree(struct tree_node *node_p, char *word)
{
  int cond;

  if (node_p == NULL)
  {
    node_p = (struct tree_node *)malloc(sizeof(struct tree_node));
    node_p->word = strdup(word);
    node_p->count = 1;
    node_p->left = node_p->right = NULL;
  }
  else if ((cond = strcmp(word, node_p->word)) == 0)
  {
    node_p->count++;
  }
  else if (cond < 0)
  {
    node_p->left = add_to_tree(node_p->left, word);
  }
  else if (cond > 0)
  {
    node_p->right = add_to_tree(node_p->right, word);
  }

  return node_p;
}

void print_tree(struct tree_node *node_p)
{
  if (node_p != NULL)
  {
    print_tree(node_p->left);
    printf("%4d %s\n", node_p->count, node_p->word);
    print_tree(node_p->right);
  }
}
