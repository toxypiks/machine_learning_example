#define NN_IMPLEMENTATION
#include <stdio.h>
#include "nn.h"

int main(void)
{
  Mat m = mat_alloc(2, 2);
  mat_print(m);
  return 0;
}
