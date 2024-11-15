#ifndef NN_H_
#define NN_H_

#include <stddef.h>
#include <stdio.h>
#include <math.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif // NN_ASSERT

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

float rand_float(void);
float sigmoidf(float x);

typedef struct {
  // shape of the data
  size_t rows;
  size_t cols;
  // to create submatrices column-wise
  size_t stride;
  // data
  float *es;
} Mat;

// print rows by:
// skipping rows by amount of columns and offset by j
#define MAT_AT(m, i, j) (m).es[(i)*(m).stride + (j)]

Mat mat_alloc(size_t rows, size_t cols);
void mat_fill(Mat m, float x);
void mat_rand(Mat m, float low, float high);
Mat mat_row(Mat m, size_t row);
void mat_copy(Mat dst, Mat src);
void mat_dot(Mat dst, Mat a, Mat b);
void mat_sum(Mat dst, Mat a);
void mat_sig(Mat m); 
void mat_print(Mat m, const char* name, size_t padding);
#define MAT_PRINT(m) mat_print(m, #m, 0)

typedef struct {
  size_t count;
  Mat *ws;
  Mat *bs;
  Mat *as; // is count+1 because of input layer
} NN;

NN nn_alloc(size_t *arch, size_t arch_count);
void nn_print(NN nn, const char* name);
void nn_rand(NN n, float low, float high);
#define NN_PRINT(nn) nn_print(nn, #nn)


#endif // NN_H_

#ifdef NN_IMPLEMENTATION

float sigmoidf(float x) {
  return 1.f / (1.f + (expf(-x)));
}

float rand_float(void)
{
  return (float)rand() / (float)RAND_MAX;
}

Mat mat_alloc(size_t rows, size_t cols)
{
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.stride = cols;
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

// creates a submatrix which only has one row of src matrix
Mat mat_row(Mat m, size_t row) {
  return (Mat) {
	.rows = 1,
	.cols = m.cols,
	.stride = m.stride,
	.es = &MAT_AT(m, row, 0),
  };
}

void mat_copy(Mat dst, Mat src) {
  NN_ASSERT(dst.rows == src.rows);
  NN_ASSERT(dst.cols == src.cols);
  for (size_t i = 0; i < dst.rows; ++i) {
	for (size_t j = 0; j < dst.cols; ++j) {
	  MAT_AT(dst, i, j) = MAT_AT(src, i, j);
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

void mat_sig(Mat m) {
  for (size_t i = 0; i < m.rows; ++i) {
	for (size_t j = 0; j < m.cols; ++j) {
	  MAT_AT(m, i, j) = sigmoidf(MAT_AT(m, i, j));
	}
  }
}

void mat_print(Mat m, const char* name, size_t padding)
{
  //%*s creates an empty string of size padding
  printf("%*s%s =[\n", (int) padding, "", name);
  for(size_t i = 0; i < m.rows; ++i) {
	printf("%*s", (int) padding, "");
	for(size_t j = 0; j < m.cols; ++j) {
	  printf("%f ", MAT_AT(m, i ,j));
	}
	printf("\n");
  }
  printf("%*s]\n", (int) padding, "");
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

// size_t arch[] = {2, 2, 1};
// NN nn = nn_alloc(arch, ARRAY_LEN(arch));

NN nn_alloc(size_t *arch, size_t arch_count)
{
  NN_ASSERT(arch_count > 0);
  NN nn;
  // arch_count has input layer thats why - 1
  nn.count = arch_count - 1;

  nn.ws = NN_MALLOC(sizeof(*nn.ws)*nn.count);
  NN_ASSERT(nn.ws != NULL);
  nn.bs = NN_MALLOC(sizeof(*nn.bs)*nn.count);
  NN_ASSERT(nn.bs != NULL);
  nn.as = NN_MALLOC(sizeof(*nn.as)*nn.count +1);
  NN_ASSERT(nn.as != NULL);

  nn.as[0] = mat_alloc(1, arch[0]);
  for (size_t i = 1; i < arch_count; ++i){
	nn.ws[i-1] = mat_alloc(nn.as[i-1].cols, arch[i]);
	nn.bs[i-1] = mat_alloc(1, arch[i]);
	nn.as[i]   = mat_alloc(1, arch[i]);
  }
  return nn;
}

void nn_print(NN nn, const char* name)
{
  char buf[256];
  printf("%s = [\n", name);
  for (size_t i = 0; i < nn.count; ++i) {
	// stores print stuff in buffer buf
	snprintf(buf, sizeof(buf), "ws%zu", i);
	// uses buf to print ws and i
	mat_print(nn.ws[i], buf, 4);
	snprintf(buf, sizeof(buf), "bs%zu", i);
	mat_print(nn.bs[i], buf, 4);
  }

  printf("]\n");
}

void nn_rand(NN nn, float low, float high)
{
  for (size_t i = 0; i < nn.count; ++i) {
	mat_rand(nn.ws[i], low, high);
	mat_rand(nn.bs[i], low, high);
  }
}

#endif // NN_IMPLEMENTATION
