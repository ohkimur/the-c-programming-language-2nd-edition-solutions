#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_MAX_SIZE 100

void push(double);
double pop(void);

int sp = 0;
double stack[STACK_MAX_SIZE];

int main(int argc, char *argv[])
{
  double op2;

  // TODO: Modify getop to read numbers from input and pass them directly to the caller. Keep the
  // type return, that will be useful if it's necessary to scale the program.
  // while ((type = getop(&op2)) != EOF)
  // {
  //   switch (type)
  //   {
  //   case NUMBER:
  //     push(op2);
  //     break;

  //   case '+':
  //     push(pop() + pop());
  //     break;

  //   case '-':
  //     op2 = pop();
  //     push(pop() - op2);
  //     break;

  //   case '*':
  //     push(pop() * pop());
  //     break;

  //   case '/':
  //     op2 = pop();

  //     if (op2 != 0.0)
  //     {
  //       push(pop() / op2);
  //     }
  //     else
  //     {
  //       printf("error: zero divisor\n");
  //     }

  //     break;

  //   case '%':
  //     op2 = pop();

  //     if (op2 != 0.0)
  //     {
  //       push((int)pop() % (int)op2);
  //     }
  //     else
  //     {
  //       printf("error: zero divisor\n");
  //     }
  //     break;

  //   case '\n':
  //     printf("result: %.8g\n", pop());
  //     break;

  //   default:
  //     printf("error: unknown command %s\n", s);
  //     break;
  //   }
  // }
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
    printf("error: stack full, can't push %g\n", f);
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
    printf("error: stack empty\n");
    return 0.0;
  }
}
