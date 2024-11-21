#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"


float td[] = {
  0, 0, 0,
  0, 1, 1,
  1, 0, 1,
  1, 1, 0,
};

int main(void) {

  srand(time(0));

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

  float eps = 1e-1;
  float rate = 1e-1;

  Mat row = mat_row(ti, 2);
  mat_copy(NN_INPUT(nn), row);
  nn_forward(nn);
  printf("cost = %f\n", nn_cost(nn, ti, to));
  nn_finite_diff(nn, g, eps, ti, to);
  nn_apply_finite_diff(nn, g, rate);
  return 0;
}
