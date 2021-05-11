#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_MAX_SIZE 100
#define MAX_LINE_LEN 1000

void push(double);
double pop(void);

size_t get_line(char line[], size_t max_line_len);

int sp = 0;
double stack[STACK_MAX_SIZE];

int main(int argc, char *argv[])
{
  char type;
  double number;
  char line[MAX_LINE_LEN];

  while (get_line(line, MAX_LINE_LEN) > 0)
  {
    if (sscanf(line, "%lf", &number) == 1)
    {
      push(number);
    }
    else if (sscanf(line, "%c", &type) == 1)
    {
      switch (type)
      {
      case '+':
        push(pop() + pop());
        break;

      case '-':
        number = pop();
        push(pop() - number);
        break;

      case '*':
        push(pop() * pop());
        break;

      case '/':
        number = pop();

        if (number != 0.0)
        {
          push(pop() / number);
        }
        else
        {
          printf("Error: zero divisor\n");
        }

        break;

      case '%':
        number = pop();

        if (number != 0.0)
        {
          push((int)pop() % (int)number);
        }
        else
        {
          printf("Error: zero divisor\n");
        }
        break;

      case '\n':
        printf("result: %.8g\n", pop());
        break;

      default:
        printf("Error: unknown command.\n");
        break;
      }
    }
  }

  return EXIT_SUCCESS;
}

void push(double f)
{
  if (sp < STACK_MAX_SIZE)
  {
    stack[sp++] = f;
  }
  else
  {
    printf("Error: stack full, can't push %g\n", f);
  }
}

double pop(void)
{
  if (sp > 0)
  {
    return stack[--sp];
  }
  else
  {
    printf("Error: stack empty\n");
    return 0.0;
  }
}

size_t get_line(char line[], size_t max_line_len)
{
  int c;
  size_t i;

  for (i = 0; i < max_line_len - 1 && (c = getc(stdin)) != EOF && c != '\n'; ++i)
  {
    line[i] = c;
  }

  if (c == '\n')
  {
    line[i] = c;
    ++i;
  }

  line[i] = '\0';

  return i;
}
