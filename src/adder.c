#define NN_IMPLEMENTATION
#include "nn.h"

#define BITS 2

int main(void) {

  // left shift operator 1 << 2 = (1*2)*2 = 4 => 4 * 4 = 16 rows
  // input are two numbers with 2 bits each at the beginning
  // BITS will get increased in the future
  size_t n = (1<<BITS);
  size_t rows = n*n;
  Mat ti = mat_alloc(rows, 2*BITS);
  Mat to = mat_alloc(rows, BITS + 1);
  for (size_t i = 0; i < ti.rows; ++i) {
    size_t x = i/n;
    size_t y = i%n;
    size_t z = x + y;
    size_t overflow = z >= n;
    for (size_t j = 0; j < BITS; ++j) {
      MAT_AT(ti, i, j) = (x>>j)&1;
      MAT_AT(ti, i, j + BITS) = (y>>j)&1;
      if (overflow) {
        MAT_AT(to, i, j) = 0;
      } else {
        MAT_AT(to, i, j) = (z>>j)&1;
      }
    }
    MAT_AT(to, i, BITS) = overflow;
  }
  MAT_PRINT(ti);
  MAT_PRINT(to);
  return 0;
}
