#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 101

struct list_node
{
  char *name;
  char *definition;
  struct list_node *next;
};

char *str_dup(char *src);
size_t hash(char *s);
struct list_node *lookup(char *s);
struct list_node *install(char *name, char *definition);

static struct list_node *hash_table[HASH_SIZE];

int main(void)
{
  install("TEST", "test");

  struct list_node *node_p = lookup("TEST");
  if (node_p == NULL)
  {
    puts("Error: hash value not found.");
  }
  else
  {
    printf("%s %s\n", node_p->name, node_p->definition);
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

size_t hash(char *s)
{
  size_t hash_value = 0;
  while (*s != '\0')
  {
    hash_value = *s + 31 * hash_value;
    ++s;
  }
  return hash_value % HASH_SIZE;
}

struct list_node *lookup(char *s)
{
  struct list_node *node_p;
  for (node_p = hash_table[hash(s)]; node_p != NULL; node_p = node_p->next)
  {
    if (strcmp(s, node_p->name) == 0)
    {
      return node_p;
    }
  }
  return NULL;
}

struct list_node *install(char *name, char *definition)
{
  struct list_node *node_p;
  size_t hash_value;

  if ((node_p = lookup(name)) == NULL)
  {
    node_p = (struct list_node *)malloc(sizeof(*node_p));
    if (node_p == NULL || (node_p->name = str_dup(name)) == NULL)
    {
      return NULL;
    }
    hash_value = hash(name);
    node_p->next = hash_table[hash_value];
    hash_table[hash_value] = node_p;
  }
  else
  {
    free((void *)node_p->definition);
  }

  if ((node_p->definition = str_dup(definition)) == NULL)
  {
    return NULL;
  }

  return node_p;
}
