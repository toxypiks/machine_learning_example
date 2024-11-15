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
  nn_rand(nn, 0, 1);

  Mat row = mat_row(ti, 2);
  MAT_PRINT(row);
  mat_copy(NN_INPUT(nn), row);
  nn_forward(nn);
  MAT_PRINT(NN_OUTPUT(nn));
  return 0;
}

