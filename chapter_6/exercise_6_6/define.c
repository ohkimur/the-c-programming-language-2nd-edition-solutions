#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 101
#define MAX_TOKEN_LEN 100

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

enum token_type
{
  NAME,
  PARENS,
  BRACKETS,
  PAREN_OPEN = '(',
  PAREN_CLOSE = ')',
  BRACKET_OPEN = '[',
  BRACKET_CLOSE = ']',
  ATTR_SEPARATOR = ','
};

// There is a strdup available with POSIX, but it's not part of ISO C.
char *str_dup(char *src);

size_t hash(char *str);
struct list_node *lookup(char *str);
struct list_node *install(char *name, char *definition);
enum boolean undef(char *name);

void skip_blanks();
void skip_comments();
void skip_string_between(char start, char end);
void skip_string_constant();

void get_name(char *dest, const size_t max_len);
int get_next_token(void);

int next_token;

char *test = "#define MAX";

char token[MAX_TOKEN_LEN];
char name[MAX_TOKEN_LEN];

static struct list_node *hash_table[HASH_SIZE];

int main(void)
{
  while (get_next_token() != EOF)
  {
    if (next_token == '#')
    {
      get_next_token();
      if (strcmp(token, "define") == 0)
      {
        get_next_token();
        puts(token);
      }
    }
  }

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
        ungetc('\n', stdin);
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

void get_name(char *dest, const size_t max_len)
{
  int c;
  size_t i = 0;
  while ((isalnum(c = getc(stdin)) || c == '_') && i < max_len)
  {
    dest[i++] = c;
  }
  dest[i] = '\0';
  ungetc(c, stdin);
}

int get_next_token(void)
{
  skip_blanks();
  skip_comments();
  skip_string_constant();

  int c = getc(stdin);
  if (c == '(')
  {
    skip_blanks();

    c = getc(stdin);
    if (c == ')')
    {
      strcpy(token, "()");
      return next_token = PARENS;
    }
    ungetc(c, stdin);

    return next_token = PAREN_OPEN;
  }
  else if (c == '[')
  {
    skip_blanks();
    get_name(token, MAX_TOKEN_LEN);
    skip_blanks();

    c = getc(stdin);
    if (c == ']')
    {
      return next_token = BRACKETS;
    }
    ungetc(c, stdin);

    return next_token = BRACKET_OPEN;
  }
  else if (isalpha(c))
  {
    ungetc(c, stdin);
    get_name(token, MAX_TOKEN_LEN);
    return next_token = NAME;
  }

  return next_token = c;
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
