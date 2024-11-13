#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

typedef struct {
 // input data
  Mat a0;
  // first layer
  Mat w1, b1, a1;
  //second layer
  Mat w2, b2, a2;
} Xor;

float cost(Xor m, Mat ti, Mat to)
{
  assert(ti.rows == to.rows);
  size_t n = ti.rows;

  for(size_t i = 0; i < n ; ++i) {
	// mat_copy(m.a0, mat_row(ti, i));
  }
}

void forward_xor(Xor m) {

  mat_dot(m.a1, m.a0, m.w1);
  mat_sum(m.a1, m.b1);
  mat_sig(m.a1);

  mat_dot(m.a2, m.a1, m.w2);
  mat_sum(m.a2, m.b2);
  mat_sig(m.a2);
}

int main(void)
{
  srand(time(0));

  Xor m;

  m.a0 = mat_alloc(1, 2);

  m.w1 = mat_alloc(2, 2);
  m.b1 = mat_alloc(1, 2);
  m.a1 = mat_alloc(1, 2);

  m.w2 = mat_alloc(2, 1);
  m.b2 = mat_alloc(1, 1);
  m.a2 = mat_alloc(1, 1);

  mat_rand(m.w1, 0, 1);
  mat_rand(m.b1, 0, 1);
  mat_rand(m.w2, 0, 1);
  mat_rand(m.b2, 0, 1);

  // create truth-table to see performance
  for(size_t i = 0; i < 2; ++i) {
	for (size_t j = 0; j < 2; ++j) {
	  MAT_AT(m.a0, 0, 0) = i;
	  MAT_AT(m.a0, 0, 1) = j;
	  forward_xor(m);
	  float y = *m.a2.es;
	  printf("%zu ^ %zu = %f\n", i, j, y);
	}
  }

  Mat test_matrix = mat_alloc(4, 4);
  mat_rand(test_matrix, 1, 5);
  mat_print(test_matrix, "test_matrix");

  Mat sub_test_matrix = mat_row(test_matrix, 1);
  mat_print(sub_test_matrix, "sub_test_matrix");

  return 0;
}
