#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minprintf(const char *fmt, ...);

int main(int argc, char *argv[])
{
  minprintf("This is a test. Let's print %d, and %f, and %s.\n", 2, 3.14159, "hello, world");
  return EXIT_SUCCESS;
}

void minprintf(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  while (*fmt)
  {
    if (*fmt == '%')
    {
      switch (*++fmt)
      {
      case 'd':
        printf("%d", va_arg(ap, int));
        break;

      case 'f':
        printf("%f", va_arg(ap, double));
        break;

      case 's':
        printf("%s", va_arg(ap, char *));
        break;

      default:
        putc(*fmt, stdout);
        break;
      }
    }
    else
    {
      putc(*fmt, stdout);
    }

    ++fmt;
  }
  va_end(ap);
}
