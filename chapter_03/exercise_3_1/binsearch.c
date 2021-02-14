#include <stdio.h>
#include <time.h>

#define MAXLEN 10000
#define ITERATIONS 100000

void initVector(int v[], int n);
void printVector(int v[], int n);

int binsearch_kr(int x, int v[], int n);
int binsearch(int x, int v[], int n);

void test_binsearch(int binsearch(int x, int v[], int n), int x, int v[], int n);

int main(void)
{
  int v[MAXLEN];

  initVector(v, MAXLEN);
  // printVector(v, MAXLEN);

  int x = -1;

  // Test binsearch_kr()
  test_binsearch(binsearch_kr, x, v, MAXLEN);

  // Test binsearch()
  test_binsearch(binsearch, x, v, MAXLEN);

  return 0;
}

void initVector(int v[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
  {
    v[i] = i;
  }
}

void printVector(int v[], int n)
{
  int i;

  printf("[ ");
  for (i = 0; i < n; ++i)
  {
    (i != n - 1) ? printf("%d, ", v[i]) : printf("%d ]\n", v[i]);
  }
}

int binsearch_kr(int x, int v[], int n)
{
  int low, mid, high;

  low = 0;
  high = n - 1;
  while (low <= high)
  {
    mid = (low + high) / 2;

    if (x < v[mid])
    {
      high = mid - 1;
    }
    else if (x > v[mid])
    {
      low = mid + 1;
    }
    else
    {
      return mid;
    }
  }

  return -1;
}

int binsearch(int x, int v[], int n)
{
  int low, mid, high;

  low = 0;
  high = n - 1;
  while (low <= high)
  {
    mid = (low + high) / 2;

    if (x < v[mid])
    {
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }

  if (x == v[low - 1])
  {
    return low - 1;
  }

  return -1;
}

void test_binsearch(int binsearch(int x, int v[], int n), int x, int v[], int n)
{
  static int test_nr = 0;
  long clocks = clock();

  int i;
  for (i = 0; i < ITERATIONS; ++i)
  {
    binsearch(x, v, n);
  }

  clocks = clock() - clocks;

  printf("test_%d: %lu clocks (%.4f seconds)\n", test_nr, clocks, (double)clocks / CLOCKS_PER_SEC);

  ++test_nr;
}

// NOTE: By using a simple test in the for loop there is a chance to increase the
// binsearch() execution speed. Just modifying an if-else statement from 3 branches
// with two condition testing to 2 branches with 1 condition testing will not
// increase drasticaly the program performance on modern machines, but is a better
// aproach.
