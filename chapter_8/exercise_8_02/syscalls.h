#define NULL 0
#define EOF (-1)
#define BUFFER_SIZE 1024
#define MAX_NR_OF_OPEN_FILES 20

struct _io_buffer_file
{
  int counter;
  char *next_char_pos_p;
  char *base;
  int flag;
  int file_descriptor;
};

typedef struct _io_buffer FILE;

extern FILE _io_buffer[MAX_NR_OF_OPEN_FILES];

#define stdin (&_io_buffer[0])
#define stdout (&_io_buffer[1])
#define stderr (&_io_buffer[2])
