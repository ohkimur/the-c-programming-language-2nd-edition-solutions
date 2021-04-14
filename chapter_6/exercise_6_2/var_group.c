#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define NR_OF_TYPES sizeof(data_types) / sizeof(data_types[0])

struct tree_node
{
  char *word;
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

int parse_arg_list(int argc, char *argv[]);

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

void skip_blanks();
void skip_comments();
void skip_chars_between(char start, char end);
void skip_char_literal(void);
void skip_string_literal(void);

int get_word(char *word, int max_word_len);
int bin_search(char *word, char *arr[], int arr_len);

char *data_types[] = {
    "char",
    "double",
    "float",
    "int",
    "long",
    "short",
    "void",
};

int var_name_str_cmp_len = 6;

int main(int argc, char *argv[])
{
  if (!parse_arg_list(argc, argv))
  {
    puts("Error: invalid arguments.");
    return EXIT_FAILURE;
  }

  int n;
  struct list_node *list_root = NULL;
  char word[MAX_WORD_LEN];

  while (get_word(word, MAX_WORD_LEN) != EOF)
  {
    if ((n = bin_search(word, data_types, NR_OF_TYPES)) >= 0)
    {
      do
      {
        // NOTE: This approach takes into consideration both variable and function names.
        if (get_word(word, MAX_WORD_LEN) != EOF && (isalpha(word[0]) || word[0] == '_'))
        {
          list_root = add_to_list(list_root, word);
        }
      } while (get_word(word, MAX_WORD_LEN) == ',');
    }
  }

  print_list(list_root);

  return EXIT_SUCCESS;
}

int parse_arg_list(int argc, char *argv[])
{
  if (argc > 2)
  {
    return 0;
  }

  if (argc == 2)
  {
    if (!isdigit(argv[1][0]))
    {
      return 0;
    }

    var_name_str_cmp_len = atoi(argv[1]);

    if (var_name_str_cmp_len < 0)
    {
      return 0;
    }
  }

  return 1;
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
        ungetc('\n', stdin);
        return;
      }
    }
  }
  ungetc(c, stdin);
}

void skip_chars_between(char start, char end)
{
  int c = getc(stdin);
  if (c == start)
  {
    while ((c = getc(stdin)) != EOF)
    {
      if (c == '\\')
      {
        if ((c = getc(stdin)) == EOF)
        {
          break;
        }
      }
      else if (c == end)
      {
        return;
      }
    }
  }
  ungetc(c, stdin);
}

void skip_char_literal(void)
{
  skip_chars_between('\'', '\'');
}

void skip_string_literal(void)
{
  skip_chars_between('"', '"');
}

int get_word(char *word, int max_word_len)
{
  skip_blanks();
  skip_comments();
  skip_char_literal();
  skip_string_literal();

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

int bin_search(char *word, char *arr[], int arr_len)
{
  int low = 0;
  int high = arr_len - 1;
  int mid;

  while (low <= high)
  {
    mid = (low + high) / 2;

    int cond = strcmp(word, arr[mid]);
    if (cond < 0)
    {
      high = mid - 1;
    }
    else if (cond > 0)
    {
      low = mid + 1;
    }
    else
    {
      return mid;
    }
  }

  return -1;
}

struct tree_node *add_to_tree(struct tree_node *node_p, char *word)
{
  int cond;

  if (node_p == NULL)
  {
    node_p = (struct tree_node *)malloc(sizeof(struct tree_node));
    node_p->word = str_dup(word);
    node_p->left = node_p->right = NULL;
  }
  else if ((cond = strcmp(word, node_p->word)) != 0)
  {
    if (cond < 0)
    {
      node_p->left = add_to_tree(node_p->left, word);
    }
    else if (cond > 0)
    {
      node_p->right = add_to_tree(node_p->right, word);
    }
  }

  return node_p;
}

void print_tree(struct tree_node *node_p)
{
  if (node_p != NULL)
  {
    print_tree(node_p->left);
    puts(node_p->word);
    print_tree(node_p->right);
  }
}

struct list_node *add_to_list(struct list_node *list_node_p, char *word)
{
  if (list_node_p == NULL)
  {
    list_node_p = (struct list_node *)malloc(sizeof(struct list_node));
    list_node_p->var_group = add_to_tree(list_node_p->var_group, word);
  }
  else if (strncmp(list_node_p->var_group->word, word, var_name_str_cmp_len) == 0)
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

// NOTE: run: ./var_group 5 < test.txt
