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

struct list_node
{
  struct tree_node *var_group;
  struct list_node *next;
};

struct tree_node *add_to_tree(struct tree_node *node_p, char *word);
void print_tree(struct tree_node *node_p);

struct list_node *add_to_list(struct list_node *list_node_p, char *word);
void print_list(struct list_node *node_p);

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

void skip_blanks();
void skip_comments();
void skip_string_between(char start, char end);
void skip_string_constant();

int get_word(char *word, int max_word_len);

int main(void)
{
  struct list_node *list_root = NULL;
  char word[MAX_WORD_LEN];

  while (get_word(word, MAX_WORD_LEN) != EOF)
  {
    // TODO: Please make this code more easy to read.
    if (isalpha(word[0]) || word[0] == '_')
    {
      if (strcmp(word, "int") == 0)
      {
        if (get_word(word, MAX_WORD_LEN) != EOF && (isalpha(word[0]) || word[0] == '_'))
        {
          list_root = add_to_list(list_root, word);
        }
      }
    }
  }

  print_list(list_root);

  return EXIT_SUCCESS;
}

char *str_dup(char *src)
{
  char *dest = (char *)malloc(strlen(src) + 1);
  if (dest != NULL)
  {
    strcpy(dest, src);
  }
  return dest;
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

  if (!isalpha(c) && c != '_')
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
    node_p->word = str_dup(word);
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

struct list_node *add_to_list(struct list_node *list_node_p, char *word)
{
  // TODO: Make the string comparison based on an external parameter.
  if (list_node_p == NULL)
  {
    list_node_p = (struct list_node *)malloc(sizeof(struct list_node));
    list_node_p->var_group = add_to_tree(list_node_p->var_group, word);
  }
  else if (strncmp(list_node_p->var_group->word, word, 4) == 0)
  {
    list_node_p->var_group = add_to_tree(list_node_p->var_group, word);
  }
  else
  {
    list_node_p->next = add_to_list(list_node_p->next, word);
  }

  return list_node_p;
}

void print_list(struct list_node *node_p)
{
  if (node_p != NULL)
  {
    print_tree(node_p->var_group);
    putchar('\n');
    print_list(node_p->next);
  }
}
