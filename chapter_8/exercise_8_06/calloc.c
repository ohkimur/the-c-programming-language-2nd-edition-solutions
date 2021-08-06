#include <stdlib.h>
#include <unistd.h>

#define MIN_NR_OF_UNITS 1024

typedef long Aling;

union header
{
  struct
  {
    union header *free_block_p;
    size_t size;
  } s;
  Aling x; // Force alignment of blocks.
};

typedef union header Header;

static Header base;
static Header *free_p = NULL;

void c_free(void *a_p);
void *c_malloc(size_t nr_of_bytes);
void *c_calloc(size_t nr_of_blocks, size_t block_size);
Header *c_morecore(size_t nr_of_units);

int main(int argc, char *argv[])
{
  // TODO: Test the following functions:
  // - [] c_malloc
  // - [] c_calloc
  // - [] c_free

  return EXIT_SUCCESS;
}

void c_free(void *a_p)
{
  Header *p;
  Header *b_p = (Header *)a_p - 1;

  for (p = free_p; !(b_p > p && b_p < p->s.free_block_p); p = p->s.free_block_p)
  {
    if (p >= p->s.free_block_p && (b_p > p || b_p < p->s.free_block_p))
    {
      break;
    }
  }

  if (b_p + b_p->s.size == p->s.free_block_p)
  {
    b_p->s.size += p->s.free_block_p->s.size;
    b_p->s.free_block_p = p->s.free_block_p->s.free_block_p;
  }
  else
  {
    b_p->s.free_block_p = p->s.free_block_p;
  }

  if (p + p->s.size == b_p)
  {
    p->s.size += b_p->s.size;
    p->s.free_block_p = b_p->s.free_block_p;
  }
  else
  {
    p->s.free_block_p = b_p;
  }

  free_p = p;
}

void *c_malloc(size_t nr_of_bytes)
{
  Header *p;
  Header *prev_p;
  size_t nr_of_units = (nr_of_bytes + sizeof(Header) - 1) / sizeof(Header);

  if ((prev_p = free_p) == NULL)
  {
    base.s.free_block_p = free_p = prev_p = &base;
    base.s.size = 0;
  }

  for (p = prev_p->s.free_block_p;; prev_p = p, p = p->s.free_block_p)
  {
    if (p->s.size >= nr_of_units)
    {
      if (p->s.size == nr_of_units)
      {
        prev_p->s.free_block_p = p->s.free_block_p;
      }
      else
      {
        p->s.size -= nr_of_units;
        p += p->s.size;
        p->s.size = nr_of_units;
      }

      free_p = prev_p;
      return (void *)(p + 1);
    }

    if (p == free_p)
    {
      if ((p = c_morecore(nr_of_units)) == NULL)
      {
        return NULL;
      }
    }
  }

  return NULL;
}

void *c_calloc(size_t nr_of_blocks, size_t block_size)
{
  // TODO: Implement this function:
  // - [] Alloc the number of blocks
  // - [] Zero out the allocated memory

  return NULL;
}

Header *c_morecore(size_t nr_of_units)
{
  char *cp;
  Header *up;

  if (nr_of_units < MIN_NR_OF_UNITS)
  {
    nr_of_units = MIN_NR_OF_UNITS;
  }

  cp = sbrk(nr_of_units * sizeof(Header));
  if (cp == (char *)-1)
  {
    return NULL;
  }

  up = (Header *)cp;
  up->s.size = nr_of_units;
  free((void *)(up + 1));

  return free_p;
}
