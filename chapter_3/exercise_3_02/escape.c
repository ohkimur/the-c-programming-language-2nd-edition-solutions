#include <stdio.h>

#define MAXLEN 1000

int get_line(char line[], unsigned int limit);
void escape(char dest[], char src[]);
void unescape(char dest[], char src[]);

int main(void)
{
  char src[MAXLEN];
  char dest[MAXLEN];

  get_line(src, MAXLEN);
  printf("%s", src);

  escape(dest, src);
  printf("%s\n", dest);

  unescape(dest, src);
  printf("%s", dest);

  return 0;
}

int get_line(char line[], unsigned int limit)
{
  int i, c;
  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
  {
    line[i] = c;
  }

  if (c == '\n')
  {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}

void escape(char dest[], char src[])
{
  int i, j;
  for (i = j = 0; src[i] != '\0'; ++i, ++j)
  {
    switch (src[i])
    {
    case '\a':
      dest[j++] = '\\';
      dest[j] = 'a';
      break;

    case '\b':
      dest[j++] = '\\';
      dest[j] = 'b';
      break;

    case '\f':
      dest[j++] = '\\';
      dest[j] = 'f';
      break;

    case '\n':
      dest[j++] = '\\';
      dest[j] = 'n';
      break;

    case '\r':
      dest[j++] = '\\';
      dest[j] = 'r';
      break;

    case '\t':
      dest[j++] = '\\';
      dest[j] = 't';
      break;

    case '\v':
      dest[j++] = '\\';
      dest[j] = 'v';
      break;

    case '\\':
      dest[j++] = '\\';
      dest[j] = '\\';
      break;

    case '\?':
      dest[j++] = '\\';
      dest[j] = '?';
      break;

    case '\'':
      dest[j++] = '\\';
      dest[j] = '\'';
      break;

    case '\"':
      dest[j++] = '\\';
      dest[j] = '"';
      break;

    default:
      dest[j] = src[i];
      break;
    }
  }

  if (src[i] == '\0')
  {
    dest[j] = src[i];
  }
}

void unescape(char dest[], char src[])
{
  int i, j;
  for (i = j = 0; src[i] != '\0'; ++i, ++j)
  {
    switch (src[i])
    {
    case '\\':
      switch (src[++i])
      {
      case 'a':
        dest[j] = '\a';
        break;

      case 'b':
        dest[j] = '\b';
        break;

      case 'f':
        dest[j] = '\f';
        break;

      case 'n':
        dest[j] = '\n';
        break;

      case 'r':
        dest[j] = '\r';
        break;

      case 't':
        dest[j] = '\t';
        break;

      case 'v':
        dest[j] = '\v';
        break;

      case '\\':
        dest[j] = '\\';
        break;

      case '?':
        dest[j] = '\?';
        break;

      case '\'':
        dest[j] = '\'';
        break;

      case '"':
        dest[j] = '\"';
        break;

      default:
        dest[j++] = '\\';
        dest[j] = src[i];
        break;
      }
      break;

    default:
      dest[j] = src[i];
      break;
    }
  }

  if (src[i] == '\0')
  {
    dest[j] = src[i];
  }
}
