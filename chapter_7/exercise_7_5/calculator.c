#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_MAX_SIZE 100
#define MAX_LINE_LEN 1000

void push(double);
double pop(void);

int sp = 0;
double stack[STACK_MAX_SIZE];

int main(int argc, char *argv[])
{
  char type;
  double number;
  char line[MAX_LINE_LEN];

  while (scanf("%s", line) != EOF)
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
