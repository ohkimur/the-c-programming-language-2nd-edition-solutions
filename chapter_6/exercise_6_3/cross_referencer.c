#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define NR_OF_TYPES sizeof(data_types) / sizeof(data_types[0])

enum boolean
{
  FALSE,
  TRUE
};

struct list_node
{
  size_t line_number;
  struct list_node *next;
};

struct tree_node
{
  char *word;
  struct list_node *line_numbers;
  struct tree_node *left;
  struct tree_node *right;
};

struct list_node *add_to_list(struct list_node *list_node_p, size_t line_number);
void print_list(struct list_node *node_p);

struct tree_node *add_to_tree(struct tree_node *node_p, char *word);
void print_tree(struct tree_node *node_p);

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

void skip_blanks();

int get_word(char *word, int max_word_len);

size_t line_number = 1;

int main(void)
{
  int c;
  struct tree_node *tree_root = NULL;
  char word[MAX_WORD_LEN];

  while ((c = get_word(word, MAX_WORD_LEN)) != EOF)
  {
    if (c == '\n')
    {
      ++line_number;
    }

    if (isalpha(word[0]))
    {
      tree_root = add_to_tree(tree_root, word);
    }
  }

  print_tree(tree_root);

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
  ungetc(c, stdin);
  word[i] = '\0';

  return word[0];
}

struct tree_node *add_to_tree(struct tree_node *node_p, char *word)
{
  int cond;

  if (node_p == NULL)
  {
    node_p = (struct tree_node *)malloc(sizeof(struct tree_node));
    node_p->line_numbers = add_to_list(node_p->line_numbers, line_number);
    node_p->word = str_dup(word);
    node_p->left = node_p->right = NULL;
  }
  else if ((cond = strcmp(word, node_p->word)) == 0)
  {
    node_p->line_numbers = add_to_list(node_p->line_numbers, line_number);
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
    printf("%s: ", node_p->word);
    print_list(node_p->line_numbers);
    putchar('\n');
    print_tree(node_p->right);
  }
}

struct list_node *add_to_list(struct list_node *list_node_p, size_t line_number)
{
  if (list_node_p == NULL)
  {
    list_node_p = (struct list_node *)malloc(sizeof(struct list_node));
    list_node_p->line_number = line_number;
    list_node_p->next = NULL;
  }
  else
  {
    list_node_p->next = add_to_list(list_node_p->next, line_number);
  }

  return list_node_p;
}

void print_list(struct list_node *node_p)
{
  static enum boolean first = TRUE;
  if (node_p != NULL)
  {
    if (first)
    {
      first = FALSE;
      printf("%zu", node_p->line_number);
    }
    else
    {
      printf(", %zu", node_p->line_number);
    }

    print_list(node_p->next);
  }
  else
  {
    first = TRUE;
  }
}

// NOTE: run: ./var_group 5 < var_group.test.c
