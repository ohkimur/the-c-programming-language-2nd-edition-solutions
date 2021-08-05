#include <stdlib.h>

typedef long Aling;

union header
{
  struct
  {
    union header *free_block_p;
    size_t size;
  };
  Aling x; // Force alignment of blocks.
};

typedef union header Header;

void *c_malloc(size_t nr_of_bytes);

int main(int argc, char *argv[])
{
  return EXIT_SUCCESS;
}

void *c_malloc(size_t nr_of_bytes)
{
  // TOOD: Implement the memory allocation here.
  return NULL;
}
