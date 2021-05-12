#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFFSIZE 100
#define MAXLEN 1000
#define NUMBER '0'

#define VARSET '_'
#define VARGET 'a'
#define VARNUM 26

enum boolean
{
  FALSE,
  TRUE
};

int get_line(char line[], unsigned int max_line_len);
int getop(char[]);

void push(double f);
double pop(void);
int is_empty(void);
void view_head(void);
void duplicate(void);
void swap(void);
void clear(void);

char var = '0';
char line[MAXLEN];
int line_i = 0;

int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  int varindex = 0;
  double var_buff[VARNUM];

  while (get_line(line, MAXLEN) != 0)
  {
    line_i = 0;
    while ((type = getop(s)) != '\0')
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

      case VARSET:
        var_buff[varindex++] = pop();
        printf("variable %c: %.3f\n", 'a' + varindex - 1, var_buff[varindex - 1]);
        break;

      case VARGET:
        push(var_buff[var - 'a']);
        break;

      case '\n':
        if (!is_empty())
        {
          printf("result: %.8g\n", pop());
        }
        break;

      default:
        printf("Error: unknown command %s.\n", s);
        break;
      }
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

int is_empty(void)
{
  if (sp > 0)
  {
    return FALSE;
  }

  return TRUE;
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

int get_line(char line[], unsigned int max_line_len)
{
  int c, i;

  for (i = 0; i < max_line_len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

int getop(char s[])
{
  int i = 0, c;

  while ((s[0] = c = line[line_i++]) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (isalpha(c))
  {
    var = c;
    return VARGET;
  }

  if (!isdigit(c) && c != '.' && c != '-')
  {
    return c;
  }

  if (c == '-')
  {
    int next = line[line_i++];
    if (!isdigit(next) && next != '.')
    {
      return next;
    }

    s[i] = c;
    c = next;
    --line_i;
  }
  else
  {
    c = line[line_i++];
  }

  if (isdigit(c))
  {
    while (isdigit(s[++i] = c = line[line_i++]))
      ;
  }

  if (c == '.')
  {
    while (isdigit(s[++i] = c = line[line_i++]))
      ;
  }

  --line_i;

  return NUMBER;
}
