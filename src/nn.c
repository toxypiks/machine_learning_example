#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

int main(void)
{
  srand(time(0));

  // weight of first layer
  Mat w1 = mat_alloc(2, 2);
  // bias of first layer
  Mat b1 = mat_alloc(1, 2);

  // second layer
  Mat w2 = mat_alloc(2, 1);
  Mat b2 = mat_alloc(1, 1);

  mat_rand(w1, 0, 1);
  mat_rand(b1, 0, 1);
  mat_rand(w2, 0, 1);
  mat_rand(b2, 0, 1);

#define MAT_PRINT(m) mat_print(m, #m)
  MAT_PRINT(w1);
  MAT_PRINT(b1);
  MAT_PRINT(w2);
  MAT_PRINT(b2);

  return 0;
}
