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
  char *sval;
  int ival;
  double dval;

  va_start(ap, fmt);
  for (; *fmt; ++fmt)
  {
    if (*fmt != '%')
    {
      putc(*fmt, stdout);
      continue;
    }

    switch (*++fmt)
    {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;

    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;

    case 's':
      for (sval = va_arg(ap, char *); *sval; ++sval)
      {
        putc(*sval, stdout);
      }
      break;

    default:
      putc(*fmt, stdout);
      break;
    }
  }

  va_end(ap);
}
