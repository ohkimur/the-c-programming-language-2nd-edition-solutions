#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_NR_OF_NODES 1000

struct tree_node
{
  char *word;
  int count;
  struct tree_node *left;
  struct tree_node *right;
};

struct tree_node *add_to_tree(struct tree_node *node_p, char *word);
void print_tree(struct tree_node *node_p);
void copy_tree_to_array(struct tree_node *arr[], struct tree_node *tree_node_p);

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

void skip_blanks();

int get_word(char *word, int max_word_len);
int tree_node_cmp(const struct tree_node *node_p_1, const struct tree_node *node_p_2);
void swap(void *v[], size_t i, size_t j);
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *));

size_t nr_of_nodes = 0;

int main(void)
{
  struct tree_node *tree_root = NULL;
  char word[MAX_WORD_LEN];

  while (get_word(word, MAX_WORD_LEN) != EOF)
  {
    if (isalpha(word[0]))
    {
      tree_root = add_to_tree(tree_root, word);
    }
  }

  struct tree_node *tree_node_list[MAX_NR_OF_NODES] = {NULL};
  copy_tree_to_array(tree_node_list, tree_root);

  quick_sort((void **)tree_node_list, 0, nr_of_nodes - 1, (int (*)(void *, void *))tree_node_cmp);

  for (size_t i = 0; i < nr_of_nodes; ++i)
  {
    printf("%4d %s\n", tree_node_list[i]->count, tree_node_list[i]->word);
  }

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

int tree_node_cmp(const struct tree_node *node_p_1, const struct tree_node *node_p_2)
{
  if (node_p_1->count > node_p_2->count)
  {
    return -1;
  }
  else if (node_p_1->count < node_p_2->count)
  {
    return 1;
  }

  return 0;
}

void swap(void *v[], size_t i, size_t j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *))
{
  if ((long)start >= (long)end)
  {
    return;
  }

  swap(v, start, (start + end) / 2);

  size_t last = start;
  for (size_t i = start + 1; i <= end; ++i)
  {
    if ((*comp)(v[i], v[start]) < 0)
    {
      swap(v, ++last, i);
    }
  }

  swap(v, start, last);
  quick_sort(v, start, last - 1, comp);
  quick_sort(v, last + 1, end, comp);
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

void copy_tree_to_array(struct tree_node *arr[], struct tree_node *tree_node_p)
{
  if (tree_node_p != NULL)
  {
    copy_tree_to_array(arr, tree_node_p->left);
    if (nr_of_nodes < MAX_NR_OF_NODES)
    {
      arr[nr_of_nodes++] = tree_node_p;
    }
    copy_tree_to_array(arr, tree_node_p->right);
  }
}

// NOTE: run: ./words_frequency < words_frequency.c
