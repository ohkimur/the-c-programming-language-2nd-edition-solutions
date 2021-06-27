#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void error(char *format, ...);
void copy_file(int from, int to);

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    copy_file(0, 1);
  }
  else
  {
    for (int file_index = 1; file_index < argc; ++file_index)
    {
      int file_descriptor;
      if ((file_descriptor = open(argv[file_index], O_RDONLY, 0)) == -1)
      {
        error("Error: could not open the file %s.", argv[file_index]);
        exit(EXIT_FAILURE);
      }

      copy_file(file_descriptor, 1);
    }
  }

  exit(EXIT_SUCCESS);
}

void copy_file(int from, int to)
{
  char buffer[BUFFER_SIZE];

  int n;
  while ((n = read(from, buffer, BUFFER_SIZE)) > 0)
  {
    write(to, buffer, n);
  }
}

void error(char *format, ...)
{
  va_list arg_p;

  va_start(arg_p, format);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, format, arg_p);
  fprintf(stderr, "\n");
  va_end(arg_p);

  exit(EXIT_FAILURE);
}
