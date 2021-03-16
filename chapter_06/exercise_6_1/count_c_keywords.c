#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define NR_OF_KEYS sizeof(keytab) / sizeof(keytab[0])

struct key
{
  char *word;
  int count;
};

int get_word(char *word, int max_word_len);
int bin_search(char *word, struct key tab[], int n);

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    /* ... */
    {"unsigned", 0},
    {"void", 0},
    {"while", 0},
};

int main(void)
{
  int n;
  char word[MAX_WORD_LEN];

  while (get_word(word, MAX_WORD_LEN) != EOF)
  {
    if (isalpha(word[0]))
    {
      if ((n = bin_search(word, keytab, NR_OF_KEYS)) >= 0)
      {
        keytab[n].count++;
      }
    }
  }

  for (size_t i = 0; i < NR_OF_KEYS; ++i)
  {
    if (keytab[i].count)
    {
      printf("%4d %s\n", keytab[i].count, keytab[i].word);
    }
  }

  return EXIT_SUCCESS;
}

int get_word(char *word, int max_word_len)
{
  int c;
  size_t i = 0;

  while (isblank(c = getc(stdin)))
    ;

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

int bin_search(char *word, struct key tab[], int n)
{
  int low = 0;
  int high = n - 1;
  int mid;

  while (low <= high)
  {
    mid = (low + high) / 2;

    int cond = strcmp(word, tab[mid].word);
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
