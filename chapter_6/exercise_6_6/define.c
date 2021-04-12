#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 101
#define MAX_LINE_LEN 1000

enum boolean
{
  FALSE,
  TRUE
};

struct list_node
{
  char *name;
  char *definition;
  struct list_node *next;
};

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

size_t hash(char *str);
struct list_node *lookup(char *str);
struct list_node *install(char *name, char *definition);
enum boolean undef(char *name);

size_t get_line(char line[], size_t max_line_len);

char *test = "#define MAX";

static struct list_node *hash_table[HASH_SIZE];

int main(void)
{
  // TODO: A different approach has to be taken here. It might be wise to consider
  // reading one line at a time, so that when necessary the macros within the
  // line can be replaced.

  // NOTE: It might be easier to research about string replace functionality, so
  // that the installed macros can be replaced with their values in the code.

  char line[MAX_LINE_LEN];

  while (get_line(line, MAX_LINE_LEN))
  {
    printf("%s", line);
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

size_t hash(char *str)
{
  size_t hash_value = 0;
  while (*str != '\0')
  {
    hash_value = *str + 31 * hash_value;
    ++str;
  }
  return hash_value % HASH_SIZE;
}

struct list_node *lookup(char *str)
{
  struct list_node *node_p;
  for (node_p = hash_table[hash(str)]; node_p != NULL; node_p = node_p->next)
  {
    if (strcmp(str, node_p->name) == 0)
    {
      return node_p;
    }
  }
  return NULL;
}

struct list_node *install(char *name, char *definition)
{
  struct list_node *node_p;
  if ((node_p = lookup(name)) == NULL)
  {
    node_p = (struct list_node *)malloc(sizeof(*node_p));
    if (node_p == NULL || (node_p->name = str_dup(name)) == NULL)
    {
      return NULL;
    }
    size_t hash_value = hash(name);
    node_p->next = hash_table[hash_value];
    hash_table[hash_value] = node_p;
  }
  else
  {
    free(node_p->definition);
  }

  if ((node_p->definition = str_dup(definition)) == NULL)
  {
    return NULL;
  }

  return node_p;
}

enum boolean undef(char *name)
{
  struct list_node *node_p;
  struct list_node *prev_node_p;
  size_t hash_value = hash(name);
  for (node_p = hash_table[hash_value], prev_node_p = NULL;
       node_p != NULL;
       prev_node_p = node_p, node_p = node_p->next)
  {
    if (strcmp(name, node_p->name) == 0)
    {
      free(node_p->name);
      free(node_p->definition);

      if (prev_node_p == NULL)
      {
        hash_table[hash_value] = node_p->next;
      }
      else
      {
        prev_node_p->next = node_p->next;
      }

      free(node_p);
      return TRUE;
    }
  }

  return FALSE;
}

size_t get_line(char line[], size_t max_line_len)
{
  int c;
  size_t i;

  for (i = 0; i < max_line_len - 1 && (c = getc(stdin)) != EOF && c != '\n'; ++i)
  {
    line[i] = c;
  }

  if (c == '\n')
  {
    line[i] = c;
    ++i;
  }

  line[i] = '\0';

  return i;
}
