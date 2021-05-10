#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_MAX_SIZE 100

#define MAXOP 100
#define NUMBER '0'

void push(double);
double pop(void);
int getop(char s[]);

int sp = 0;
double stack[STACK_MAX_SIZE];

int main(int argc, char *argv[])
{
  int type;
  double op2;
  char s[MAXOP];

  // TODO: Modify getop to read numbers from input and pass them directly to the caller. Keep the
  // type return, that will be useful if it's necessary to scale the program.
  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      break;

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
        printf("error: zero divisor\n");
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
        printf("error: zero divisor\n");
      }
      break;

    case '\n':
      printf("result: %.8g\n", pop());
      break;

    default:
      printf("error: unknown command %s\n", s);
      break;
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

int getop(char s[])
{
  int i = 0, c;

  while ((s[0] = c = getc(stdin)) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-')
  {
    return c;
  }

  if (c == '-')
  {
    int next = getc(stdin);
    if (!isdigit(next) && next != '.')
    {
      return next;
    }

    s[i] = c;
    ungetc(c = next, stdin);
  }
  else
  {
    c = getc(stdin);
  }

  if (isdigit(c))
  {
    while (isdigit(s[++i] = c = getc(stdin)))
      ;
  }

  if (c == '.')
  {
    while (isdigit(s[++i] = c = getc(stdin)))
      ;
  }

  if (c != EOF)
  {
    ungetc(c, stdin);
  }

  return NUMBER;
}
