#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minprintf(const char *format, ...);

int main(int argc, char *argv[])
{
  int a;
  minprintf("Let's print %d, %i, %o, %x, %X, %u, %c, %e, %E, %g, %G, %f, %p, and %s.\n",
            2, 3, 8, 16, 16, -1, 97, 0.0025f, 0.0023f, 0.0025f, 0.0023f, 3.14159f, &a, "hello, world");
  return EXIT_SUCCESS;
}

void minprintf(const char *format, ...)
{
  va_list arg_p;

  va_start(arg_p, format);
  for (; *format != '\0'; ++format)
  {
    if (*format != '%')
    {
      putc(*format, stdout);
      continue;
    }

    switch (*++format)
    {
    case 'd':
    case 'i':
      printf("%d", va_arg(arg_p, int));
      break;

    case 'o':
      printf("%o", va_arg(arg_p, int));
      break;

    case 'x':
    case 'X':
      printf("%x", va_arg(arg_p, int));
      break;

    case 'u':
      printf("%u", va_arg(arg_p, int));
      break;

    case 'c':
      printf("%c", va_arg(arg_p, int));
      break;

    case 's':
      printf("%s", va_arg(arg_p, char *));
      break;

    case 'f':
      printf("%f", va_arg(arg_p, double));
      break;

    case 'e':
    case 'E':
      printf("%e", va_arg(arg_p, double));
      break;

    case 'g':
    case 'G':
      printf("%g", va_arg(arg_p, double));
      break;

    case 'p':
      printf("%p", va_arg(arg_p, void *));
      break;

    default:
      putc(*format, stdout);
      break;
    }
  }
  va_end(arg_p);
}
