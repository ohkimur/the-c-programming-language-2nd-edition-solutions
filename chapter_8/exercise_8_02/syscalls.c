#include <unistd.h>
#include <fcntl.h>
#include "syscalls.h"

#define PERMISSIONS 0666 // RW for owners, group, others

FILE *fopen(char *name, char *mode)
{
  int file_descriptor;
  FILE *file_p;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
  {
    return NULL;
  }

  for (file_p = _io_buffer; file_p < _io_buffer + MAX_NR_OF_OPEN_FILES; ++file_p)
  {
    if ((file_p->flag & (_READ | _WRITE)) == 0)
    {
      break; // found free slot
    }

    if (file_p >= _io_buffer + MAX_NR_OF_OPEN_FILES)
    {
      return NULL; // no free slots
    }

    if (*mode == 'w')
    {
      file_descriptor = creat(name, PERMISSIONS);
    }
    else if (*mode == 'a')
    {
      if ((file_descriptor = open(name, O_WRONLY, 0)) == -1)
      {
        file_descriptor = creat(name, PERMISSIONS);
      }
      lseek(file_descriptor, 0L, 2);
    }
    else
    {
      file_descriptor = open(name, O_RDONLY, 0);
    }

    if (file_descriptor == -1)
    {
      return NULL; // couldn't access name
    }

    file_p->file_descriptor = file_descriptor;
    file_p->counter = 0;
    file_p->base = NULL;
    file_p->flag = (*mode == 'r') ? _READ : _WRITE;

    return file_p;
  }
}
