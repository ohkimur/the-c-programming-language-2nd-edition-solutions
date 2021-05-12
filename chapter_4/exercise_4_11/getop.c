#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFFSIZE 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

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

    case '\n':
      printf("result: %.8g\n", pop());
      break;

    default:
      printf("Error: unknown command %s.\n", s);
      break;
    }
  }

  return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL)
  {
    val[sp++] = f;
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
    return val[--sp];
  }
  else
  {
    printf("Error: stack empty.\n");
    return 0.0;
  }
}

int getop(char s[])
{
  int i = 0, c;
  static int buf = EOF;

  while ((s[0] = c = getchar()) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-')
  {
    return c;
  }

  if (c == '-')
  {
    int next = getchar();
    if (!isdigit(next) && next != '.')
    {
      return next;
    }

    s[i] = c;
    c = next = buf;
  }
  else
  {
    c = getchar();
  }

  if (isdigit(c))
  {
    while (isdigit(s[++i] = c = getchar()))
      ;
  }

  if (c == '.')
  {
    while (isdigit(s[++i] = c = getchar()))
      ;
  }

  if (c != EOF)
  {
    buf = c;
  }

  return NUMBER;
}
