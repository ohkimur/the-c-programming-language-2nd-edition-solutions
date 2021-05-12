#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_MAX_SIZE 100
#define MAX_STR_LEN 1000

void push(double);
double pop(void);

int sp = 0;
double stack[STACK_MAX_SIZE];

int main(int argc, char *argv[])
{
  char c;
  double op2;
  char str[MAX_STR_LEN];

  while (scanf("%s", str) != EOF)
  {
    if (sscanf(str, "%lf", &op2) == 1)
    {
      push(op2);
    }
    else if (sscanf(str, "%c", &c) == 1)
    {
      switch (c)
      {
      case '+':
        push(pop() + pop());
        break;

      case '-':
        op2 = pop();
        push(pop() - op2);
        break;

      case '*':
        push(pop() * pop());
        break;

      case '/':
        op2 = pop();

        if (op2 != 0.0)
        {
          push(pop() / op2);
        }
        else
        {
          printf("Error: zero divisor.\n");
        }
        break;

      case '%':
        op2 = pop();

        if (op2 != 0.0)
        {
          push((int)pop() % (int)op2);
        }
        else
        {
          printf("Error: zero divisor.\n");
        }
        break;

      default:
        printf("Error: unknown command.\n");
        break;
      }
    }
  }

  printf("result: %.8g\n", pop());

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
    printf("Error: stack full, can't push %g.\n", f);
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
    printf("Error: stack empty.\n");
    return 0.0;
  }
}

// NOTE: run: ./calculator <<< "2 3 4 2 - + +"
