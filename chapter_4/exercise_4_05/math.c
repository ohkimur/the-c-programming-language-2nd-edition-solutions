#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFFSIZE 100
#define NUMBER '0'

int getop(char[]);

void push(double f);
double pop(void);
void view_head(void);
void duplicate(void);
void swap(void);
void clear(void);

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

    case '^':
      op2 = pop();
      push(pow(pop(), op2));
      break;

    case '~':
      push(sin(pop()));
      break;

    case 'e':
      push(exp(pop()));
      break;

    case 'h':
      view_head();
      break;

    case 'd':
      duplicate();
      break;

    case 's':
      swap();
      break;

    case 'c':
      clear();
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
double stack[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL)
  {
    stack[sp++] = f;
  }
  else
  {
    printf("Error: stack full.\n");
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
  }

  return 0.0;
}

void view_head(void)
{
  if (sp)
  {
    printf("stack_head: %g\n", stack[sp - 1]);
  }
  else
  {
    printf("Error: stack empty.\n");
  }
}

void duplicate(void)
{
  double temp = pop();
  push(temp);
  push(temp);
}

void swap(void)
{
  double temp1 = pop();
  double temp2 = pop();

  push(temp1);
  push(temp2);
}

void clear(void)
{
  do
  {
    stack[sp] = 0.0;
  } while (sp--);
}

int bufp = 0;
char buf[BUFFSIZE];

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFFSIZE)
  {
    printf("ungetch: too many characters\n");
  }
  else
  {
    buf[bufp++] = c;
  }
}

int getop(char s[])
{
  int i = 0, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-')
  {
    return c;
  }

  if (c == '-')
  {
    int next = getch();
    if (!isdigit(next) && next != '.')
    {
      return next;
    }

    s[i] = c;
    ungetch(c = next);
  }
  else
  {
    c = getch();
  }

  if (isdigit(c))
  {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  if (c == '.')
  {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  if (c != EOF)
  {
    ungetch(c);
  }

  return NUMBER;
}
