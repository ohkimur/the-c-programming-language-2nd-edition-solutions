// #define NULL 0
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

typedef struct _io_buffer_file FILE;

extern FILE _io_buffer[MAX_NR_OF_OPEN_FILES];

#define stdin (&_io_buffer[0])
#define stdout (&_io_buffer[1])
#define stderr (&_io_buffer[2])

enum _flags
{
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020
};

int _fill_buffer(FILE *);
int _flush_buffer(FILE *);

#define feof(p) ((p->flag & _EOF) != 0)
#define ferror(p) ((p->flag & _ERR) != 0)
#define fileno(p) ((p->file_descriptor)

#define getc(p) (--p->couter >= 0) ? (unsigned char) *(p)->next_char_pos_p++ : _fill_buffer(p))
#define putc(x, p) (--p->counter >= 0) ? *p->next_char_pos_p++ = x : _flush_buffer(x,p))

#define getchar() getc(stdin)
#define putchar(x) putc(x, stdout)
