#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

int main(void)
{
  srand(time(0));

  // input data
  Mat x = mat_alloc(1, 2);

  // weight of first layer
  Mat w1 = mat_alloc(2, 2);
  // bias of first layer
  Mat b1 = mat_alloc(1, 2);

  // result matrix first layer
  Mat a1 = mat_alloc(1, 2);

  // second layer
  Mat w2 = mat_alloc(2, 1);
  Mat b2 = mat_alloc(1, 1);

  // result matrix second layer
  Mat a2 = mat_alloc(1, 2);

  mat_rand(w1, 0, 1);
  mat_rand(b1, 0, 1);
  mat_rand(w2, 0, 1);
  mat_rand(b2, 0, 1);

  // forwarding data to next layer
  // x = {0, 1};
  float x1 = 0;
  float x2 = 1;
  MAT_AT(x, 0, 0) = x1;
  MAT_AT(x, 0, 1) = x2;

  mat_dot(a1, x, w1);
  mat_sum(a1, b1);
  mat_sig(a1);

  mat_dot(a2, a1, w2);
  mat_sum(a2, b2);
  mat_sig(a2);

  float y = *a2.es;

  // sigmoid(x*w1 + b1)

  MAT_PRINT(w1);
  MAT_PRINT(b1);
  MAT_PRINT(w2);
  MAT_PRINT(b2);

  return 0;
}
