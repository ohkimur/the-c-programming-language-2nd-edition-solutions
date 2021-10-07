#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
void c_bfree(void *a_p, size_t block_size);
void *c_malloc(size_t nr_of_bytes);
void *c_calloc(size_t nr_of_blocks, size_t block_size);
Header *c_morecore(size_t nr_of_units);

int main(int argc, char *argv[])
{
  char *test_malloc_str_p;
  if ((test_malloc_str_p = c_malloc(27 * sizeof(char))) == NULL)
  {
    printf("Error: malloc faild to allocate the requrested memory.\n");
    return EXIT_FAILURE;
  }

  strcpy(test_malloc_str_p, "Content from malloc here.");
  printf("%s\n", test_malloc_str_p);
  c_free(test_malloc_str_p);

  char *test_calloc_str_p;
  if ((test_calloc_str_p = c_calloc(27, sizeof(char))) == NULL)
  {
    printf("Error: calloc faild to allocate the requrested memory.\n");
    return EXIT_FAILURE;
  }

  strcpy(test_calloc_str_p, "Content from calloc here.");
  printf("%s\n", test_calloc_str_p);
  c_free(test_calloc_str_p);

  char test_bfree[1024] = "Some test content here.";
  c_bfree(test_bfree, 1024);

  return EXIT_SUCCESS;
}

void c_free(void *a_p)
{
  Header *p;
  Header *b_p = (Header *)a_p - 1;

  if (b_p->s.size == 0 || b_p->s.size == UINT_MAX - MIN_NR_OF_UNITS)
  {
    fprintf(stderr, "Error(free): invalid block size %zu\n", b_p->s.size);
    return;
  }

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

void c_bfree(void *p, size_t block_size)
{
  Header *b_p;

  if (block_size < MIN_NR_OF_UNITS)
  {
    fprintf(stderr, "Error: block must be at least of size %d\n", MIN_NR_OF_UNITS);
    return;
  }

  b_p = (Header *)p;
  b_p->s.size = (block_size / sizeof(Header)) - 1;
  c_free((void *)(b_p + 1));
}

void *c_malloc(size_t nr_of_bytes)
{
  Header *p;
  Header *prev_p;

  if (nr_of_bytes == 0 || nr_of_bytes >= UINT_MAX - MIN_NR_OF_UNITS)
  {
    fprintf(stderr, "Error(malloc): invalid size %zu\n", nr_of_bytes);
    return NULL;
  }

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
  void *p = NULL;
  if ((p = c_malloc(nr_of_blocks * block_size)) == NULL)
  {
    return NULL;
  }
  memset(p, 0, nr_of_blocks * block_size);

  return p;
}

Header *c_morecore(size_t nr_of_units)
{
  char *c_p;
  Header *u_p;

  if (nr_of_units < MIN_NR_OF_UNITS)
  {
    nr_of_units = MIN_NR_OF_UNITS;
  }

  c_p = sbrk(nr_of_units * sizeof(Header));
  if (c_p == (char *)-1)
  {
    return NULL;
  }

  u_p = (Header *)c_p;
  u_p->s.size = nr_of_units;
  c_free((void *)(u_p + 1));

  return free_p;
}
