#ifndef NN_H_
#define NN_H_

#include <stddef.h>
#include <stdio.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif // NN_ASSERT

typedef struct {
  // shape of the data
  size_t rows;
  size_t cols;
  // data
  float *es;
} Mat;

// print rows by:
// skipping rows by amount of columns and offset by j
#define MAT_AT(m, i, j) (m).es[(i)*(m).cols + (j)]

float rand_float(void);

Mat mat_alloc(size_t rows, size_t cols);
void mat_rand(Mat m);
void mat_dot(Mat dst, Mat a, Mat b);
void mat_sum(Mat dst, Mat a);
void mat_print(Mat m);

#endif // NN_H_

#ifdef NN_IMPLEMENTATION

float rand_float(void)
{
  return (float)rand() / (float)RAND_MAX;
}

Mat mat_alloc(size_t rows, size_t cols)
{
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.es = NN_MALLOC(sizeof(*m.es)*rows*cols);
  NN_ASSERT(m.es != NULL);
  return m;
}
void mat_dot(Mat dst, Mat a, Mat b)
{
  //not implemented yet
  (void) dst;
  (void) a;
  (void) b;
}
void mat_sum(Mat dst, Mat a)
{
  //not implemented yet
  (void) dst;
  (void) a;
}
void mat_print(Mat m)
{
  for(size_t i = 0; i < m.rows; ++i) {
	for(size_t j = 0; j < m.cols; ++j) {
	  printf("%f ", MAT_AT(m, i ,j));
	}
	printf("\n");
  }
}

void mat_rand(Mat m) {
  for(size_t i = 0; i < m.rows; ++i) {
	for(size_t j = 0; j < m.cols; ++j) {
	  MAT_AT(m, i, j) = rand_float();
	}
  }
}

#endif // NN_IMPLEMENTATION
