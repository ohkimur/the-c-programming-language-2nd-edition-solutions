#include <stdlib.h>

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

Header *morecore(size_t nr_of_units);
void *c_malloc(size_t nr_of_bytes);

int main(int argc, char *argv[])
{
  return EXIT_SUCCESS;
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
      if ((p = morecore(nr_of_units)) == NULL)
      {
        return NULL;
      }
    }
  }

  return NULL;
}
