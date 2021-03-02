#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 15

unsigned char stack_pointer = 0;
float stack[STACK_SIZE];

float pop(void);
void push(float element);

int main(int argc, char *argv[])
{
  char error = 0;

  for (size_t i = 1; i < argc; ++i)
  {
    float number = atof(argv[i]);

    if (number || strcmp(argv[i], "0") == 0)
    {
      push(number);
    }
    else if (strlen(argv[i]) == 1)
    {
      if (stack_pointer >= 2 && stack_pointer < STACK_SIZE)
      {
        float number2 = pop();
        float number1 = pop();

        char op = *argv[i];
        switch (op)
        {
        case '+':
          push(number1 + number2);
          break;

        case '-':
          push(number1 - number2);
          break;

        case '*': // This char might require to be escaped when passed as an argument.
          push(number1 * number2);
          break;

        case '/':
          if (number2 == 0)
          {
            error = 4;
          }
          else
          {
            push(number1 / number2);
          }
          break;

        default:
          error = 3;
          break;
        }
      }
      else
      {
        error = 2;
      }
    }
    else
    {
      error = 1;
    }
  }

  if (error)
  {
    switch (error)
    {
    case 1:
      printf("ERROR: Arguments should be numbers or one of the following mathematical operations: '+', '-', '*', '/'\n");
      break;

    case 2:
      printf("ERROR: Too many or too few arguments.\n");
      break;

    case 3:
      printf("ERROR: Invalid operation. Use one of the following mathematical operations: '+', '-', '*', '/'\n");
      break;

    case 4:
      printf("ERROR: Division by zero (NaN).\n");
      break;

    default:
      break;
    }

    return EXIT_FAILURE;
  }

  printf("result: %.3f", pop());

  return EXIT_SUCCESS;
}

float pop(void)
{
  if (stack_pointer > 0)
  {
    return stack[stack_pointer--];
  }

  printf("ERROR: The stack is empty.\n");
  return 0;
}

void push(float element)
{
  if (stack_pointer < STACK_SIZE)
  {
    stack[++stack_pointer] = element;
  }
  else
  {
    printf("ERROR: The stack is full.\n");
  }
}
