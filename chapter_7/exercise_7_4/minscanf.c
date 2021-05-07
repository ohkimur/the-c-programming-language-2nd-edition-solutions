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

    default:
      break;
    }
  }
  va_end(arg_p);
}
