#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 15

unsigned char stack_pointer = 0;
int stack[STACK_SIZE];

int pop(void);
void push(int element);

int main(int argc, char *argv[])
{
  char error = 0;

  unsigned int i = 1;
  for (i = 1; i < argc; ++i)
  {
    int number = atoi(argv[i]);

    // TODO: Check for 0 vs "0" cornercase.
    if (number)
    {
      push(number);
    }
    else if (strlen(argv[i]) == 1)
    {
      int number2 = pop();
      int number1 = pop();

      char op = *argv[i];
      switch (op)
      {
      case '+':
        push(number1 + number2);
        break;

      case '-':
        push(number1 - number2);
        break;

      case '*':
        push(number1 * number2);
        break;

      case '/':
        if (number2 < 0)
        {
          error++;
        }
        else
        {
          push(number1 / number2);
        }
        break;

      default:
        error++;
        break;
      }
    }
    else
    {
      error++;
    }
  }

  if (error)
  {
    printf("ERROR: Arguments should be numbers or one of the following mathematical operations: '+', '-', '*', '/'\n");
  }
  else
  {
    printf("result: %d", pop());
  }

  return 0;
}

int pop(void)
{
  return stack[stack_pointer--];
}

void push(int element)
{
  stack[++stack_pointer] = element;
}
