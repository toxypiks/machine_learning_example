#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

int main(void)
{
  srand(time(0));
  Mat a = mat_alloc(1, 2);
  mat_rand(a, 5, 10);

  Mat b = mat_alloc(2, 2);
  mat_fill(b, 0);

  Mat dst = mat_alloc(1, 2);

  mat_print(a);
  printf("--------------------\n");
  mat_dot(dst, a, b);
  mat_print(dst);

  return 0;
}
