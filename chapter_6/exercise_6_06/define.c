#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 101
#define MAX_LINE_LEN 1000
#define MAX_WORD_LEN 100

enum boolean
{
  FALSE,
  TRUE
};

enum directive_type
{
  NONE = 0,
  DEFINE = 1,
  UNDEF = 2
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

int get_word(char *word, size_t max_word_len);
size_t get_alnum_str(char *str, size_t max_str_len);

void consume_word(char *word, char *Error_str);
void consume_blanks(void);
void consume_comments(void);
void consume_chars_between(char start, char end);
void consume_char_literal(void);
void consume_string_literal(void);
void consume_preproc(void);

static struct list_node *hash_table[HASH_SIZE];

int main(void)
{
  int c;
  char word[MAX_WORD_LEN];
  while ((c = get_word(word, MAX_WORD_LEN)) != EOF)
  {
    if (isalpha(c))
    {
      struct list_node *node_p = lookup(word);
      if (node_p != NULL)
      {
        printf("%s", node_p->definition);
      }
      else
      {
        printf("%s", word);
      }
    }
    else
    {

      if (c == '/')
      {
        ungetc(c, stdin);
        consume_comments();
      }
      else if (c == '\'')
      {
        ungetc(c, stdin);
        consume_char_literal();
      }
      else if (c == '"')
      {
        ungetc(c, stdin);
        consume_string_literal();
      }
      else if (c == '#')
      {
        ungetc(c, stdin);
        consume_preproc();
      }
      else
      {
        putc(c, stdout);
      }
    }
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

int get_word(char *word, size_t max_word_len)
{
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

size_t get_alnum_str(char *str, size_t max_str_len)
{
  size_t i = 0;
  int c;
  while (isalnum(c = getc(stdin)) && i < max_str_len)
  {
    str[i++] = c;
  }
  str[i] = '\0';
  ungetc(c, stdin);
  return i;
}

void consume_word(char *word, char *Error_str)
{
  int c;
  if ((c = get_word(word, MAX_WORD_LEN)) == EOF)
  {
    ungetc(c, stdin);
    return;
  }
  else if (!isalpha(c))
  {
    puts(Error_str);
  }
  printf("%s", word);
}

void consume_blanks(void)
{
  int c;
  while (isblank(c = getc(stdin)))
  {
    putc(c, stdout);
  }
  ungetc(c, stdin);
}

void consume_comments(void)
{
  int c = getc(stdin);
  if (c == '/')
  {
    putc(c, stdout);

    c = getc(stdin);
    if (c == '/')
    {
      putc(c, stdout);
      while ((c = getc(stdin)) != '\n' && c != EOF)
      {
        putc(c, stdout);
      }
    }
    else if (c == '*')
    {
      putc(c, stdout);
      while ((c = getc(stdin)) != EOF)
      {
        putc(c, stdout);
        if (c == '*')
        {
          c = getc(stdin);
          putc(c, stdout);
          if (c == '/')
          {
            break;
          }
        }
      }

      c = getc(stdin);
      if (c == '/')
      {
        putc(c, stdout);
        return;
      }
    }
  }
  ungetc(c, stdin);
}

void consume_chars_between(char start, char end)
{
  int c = getc(stdin);
  if (c == start)
  {
    putc(c, stdout);
    while ((c = getc(stdin)) != EOF)
    {
      putc(c, stdout);
      if (c == '\\')
      {
        c = getc(stdin);
        putc(c, stdout);
        if (c == EOF)
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

void consume_char_literal(void)
{
  consume_chars_between('\'', '\'');
}

void consume_string_literal(void)
{
  consume_chars_between('"', '"');
}

void consume_preproc(void)
{
  int c = getc(stdin);
  if (c == '#')
  {
    putc(c, stdout);

    char word[MAX_WORD_LEN];
    consume_word(word, "Error: expected preprocessor directive.");

    enum directive_type directive = NONE;
    if (strcmp(word, "define") == 0)
    {
      directive = DEFINE;
    }
    else if (strcmp(word, "undef") == 0)
    {
      directive = UNDEF;
    }

    if (directive)
    {
      consume_blanks();
      consume_word(word, "Error: invalid name.");
    }

    if (directive == DEFINE)
    {
      consume_blanks();
      char definition[MAX_WORD_LEN];
      get_alnum_str(definition, MAX_WORD_LEN);
      printf("%s", definition);

      struct list_node *node_p = lookup(definition);
      if (node_p != NULL)
      {
        install(word, node_p->definition);
      }
      else
      {
        install(word, definition);
      }
    }
    else if (directive == UNDEF)
    {
      undef(word);
    }
  }
  else
  {
    ungetc(c, stdin);
  }
}

// NOTE: run: ./define < define.c
