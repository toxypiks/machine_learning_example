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
void mat_fill(Mat m, float x);
void mat_rand(Mat m, float low, float high);
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
  NN_ASSERT(a.cols == b.rows);
  size_t n = a.cols;
  NN_ASSERT(dst.rows == a.rows);
  NN_ASSERT(dst.cols == b.cols);

  for (size_t i = 0; i < dst.rows; ++i) {
	for (size_t j = 0; j < dst.cols; ++j) {
	  MAT_AT(dst, i, j) = 0;
	  for (size_t k = 0; k < n; ++k) {
		MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
	  }
	}
  }
}
void mat_sum(Mat dst, Mat a)
{
  NN_ASSERT(dst.rows == a.rows);
  NN_ASSERT(dst.cols == a.cols);
  for (size_t i = 0; i < dst.rows; ++i) {
	for (size_t j = 0; j < dst.cols; ++j) {
	  MAT_AT(dst, i, j) += MAT_AT(a, i ,j);
	}
  }
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

void mat_fill(Mat m, float x) {
  for(size_t i = 0; i < m.rows; ++i) {
	for(size_t j = 0; j < m.cols; ++j) {
	  MAT_AT(m, i ,j) = x;
	}
  }
}

void mat_rand(Mat m, float low, float high) {
  for(size_t i = 0; i < m.rows; ++i) {
	for(size_t j = 0; j < m.cols; ++j) {
	  // rand_float times range but starting at low (offset low by adding low)
	  MAT_AT(m, i, j) = rand_float()*(high-low) + low;
	}
  }
}

#endif // NN_IMPLEMENTATION
