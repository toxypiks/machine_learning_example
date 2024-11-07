#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

int main(void)
{
  srand(time(0));
  Mat a = mat_alloc(2, 2);
  mat_fill(a, 1);
  Mat b = mat_alloc(2, 2);
  mat_fill(b, 1);

  mat_print(a);
  printf("---------\n");
  mat_sum(a, b);
  mat_print(a);

  return 0;
}
