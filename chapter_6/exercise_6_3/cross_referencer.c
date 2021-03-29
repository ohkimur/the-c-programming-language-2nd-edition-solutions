#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define NR_OF_LINKING_WORDS sizeof(linking_words) / sizeof(linking_words[0])

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

struct tree_node *add_to_tree(struct tree_node *node_p, char *word, size_t line_number);
void print_tree(struct tree_node *node_p);

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

void skip_blanks();

int get_word(char *word, int max_word_len);
int bin_search(char *word, char *arr[], int arr_len);

char *linking_words[] = {
    "And",
    "As",
    "But",
    "For",
    "Like",
    "Nor",
    "Or",
    "So",
    "The",
    "Then",
    "To",
    "Too",
    "Yet",
    "and",
    "as",
    "but",
    "for",
    "like",
    "nor",
    "or",
    "so",
    "the",
    "then",
    "to",
    "too",
    "yet",
};

int main(void)
{
  size_t line_number = 1;
  char word[MAX_WORD_LEN];
  struct tree_node *tree_root = NULL;

  while (get_word(word, MAX_WORD_LEN) != EOF)
  {
    if (word[0] == '\n')
    {
      ++line_number;
    }
    else if (isalpha(word[0]))
    {
      if (bin_search(word, linking_words, NR_OF_LINKING_WORDS) == -1)
      {
        tree_root = add_to_tree(tree_root, word, line_number);
      }
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

int get_word(char *word, int max_word_len)
{
  skip_blanks();

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

struct tree_node *add_to_tree(struct tree_node *node_p, char *word, size_t line_number)
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
    node_p->left = add_to_tree(node_p->left, word, line_number);
  }
  else if (cond > 0)
  {
    node_p->right = add_to_tree(node_p->right, word, line_number);
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

// NOTE: run: ./cross_referencer < test.txt
