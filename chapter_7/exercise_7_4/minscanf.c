#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minscanf(const char *format, ...);

int main(int argc, char *argv[])
{
  int a = 0;
  int b = 0;

  minscanf("%d %d", &a, &b);
  printf("a: %d, b: %d\n", a, b);

  return EXIT_SUCCESS;
}

void minscanf(const char *format, ...)
{
  va_list arg_p;

  va_start(arg_p, format);
  for (; *format != '\0'; ++format)
  {
    if (*format != '%')
    {
      continue;
    }

    switch (*++format)
    {
    case 'd':
      scanf("%d", va_arg(arg_p, int *));
      break;

    case 'i':
      scanf("%i", va_arg(arg_p, int *));
      break;

    case 'o':
      scanf("%o", va_arg(arg_p, int *));
      break;

    case 'u':
      scanf("%u", va_arg(arg_p, unsigned int *));
      break;

    case 'x':
      scanf("%x", va_arg(arg_p, int *));
      break;

    case 'c':
      scanf("%c", va_arg(arg_p, char *));
      break;

    case 's':
      scanf("%s", va_arg(arg_p, char *));
      break;

    case 'e':
    case 'f':
    case 'g':
      scanf("%f", va_arg(arg_p, float *));
      break;

    default:
      break;
    }
  }
  va_end(arg_p);
}
