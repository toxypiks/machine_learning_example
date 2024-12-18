#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"


float td[] = {
  0, 0, 0,
  0, 1, 1,
  1, 0, 1,
  1, 1, 1,
};

int main(void) {

  // srand(time(0));

  srand(69);

  size_t stride = 3;
  // create submatrix out of columns td
  size_t n = sizeof(td)/sizeof(td[0])/3;

  Mat ti = {
	.rows = n,
	.cols = 2,
	.stride = stride,
	.es = td,
  };

  Mat to = {
	.rows = n,
	.cols = 1,
	.stride = stride,
	.es = td  + 2,
  };

  size_t arch[] = {2, 2, 1};
  NN nn = nn_alloc(arch, ARRAY_LEN(arch));
  NN g = nn_alloc(arch, ARRAY_LEN(arch));
  nn_rand(nn, 0, 1);

  float rate = 1;

  printf("cost = %f\n", nn_cost(nn, ti, to));
  for (size_t i = 0; i < 5000; ++i) {
#if 0
    float eps = 1e-1;
    nn_finite_diff(nn, g, eps, ti, to);
#else
	nn_backprop(nn, g, ti, to);
#endif
    nn_apply_finite_diff(nn, g, rate);
    printf("cost = %f\n", nn_cost(nn, ti, to));
  }

  for (size_t i = 0; i < 2; ++i) {
	for (size_t j = 0; j < 2; ++j) {
	  MAT_AT(NN_INPUT(nn), 0, 0) = i;
	  MAT_AT(NN_INPUT(nn), 0, 1) = j;
	  nn_forward(nn);
	  printf("%zu ^ %zu = %f\n", i, j, MAT_AT(NN_OUTPUT(nn), 0, 0));
	}
  }
  return 0;
}
