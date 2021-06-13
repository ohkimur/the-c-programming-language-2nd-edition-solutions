#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minscanf(const char *format, ...);

int main(int argc, char *argv[])
{
  int decimal;
  int integer;
  int octal;
  int unsigned_decimal;
  int hexadecimal_integer;
  char character;
  char str[100];
  float float_point_number;

  minscanf("%d", &decimal);
  minscanf("%i", &integer);
  minscanf("%o", &octal);
  minscanf("%u", &unsigned_decimal);
  minscanf("%x", &hexadecimal_integer);
  minscanf("%c", &character);
  minscanf("%s", str);
  minscanf("%f", &float_point_number);

  printf("decimal: %d\n", decimal);
  printf("integer: %i\n", integer);
  printf("octal: %o\n", octal);
  printf("unsigned_decimal: %u\n", unsigned_decimal);
  printf("hexadecimal_integer: %x\n", hexadecimal_integer);
  printf("character: %c\n", character);
  printf("str: %s\n", str);
  printf("float_point_number: %f\n", float_point_number);

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

// NOTE: run: ./minscanf <<< "1 2 3 4 5r hello 2.3"
// In Unix like systems:< file or directory, << here doc, <<< here string
