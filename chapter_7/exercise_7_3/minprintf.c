#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minprintf(const char *fmt, ...);

int main(int argc, char *argv[])
{
  minprintf("This is a test. Let's print %d, %i, %o, and %f, and %s.\n", 2, 3, 7, 3.14159, "hello, world");
  return EXIT_SUCCESS;
}

void minprintf(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  for (; *fmt != '\0'; ++fmt)
  {
    if (*fmt != '%')
    {
      putc(*fmt, stdout);
      continue;
    }

    switch (*++fmt)
    {
    case 'd':
    case 'i':
      printf("%d", va_arg(ap, int));
      break;

    case 'o':
      printf("%o", va_arg(ap, int));
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
  va_end(ap);
}
