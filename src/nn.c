#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

int main(void) {

  srand(time(0));

  size_t arch[] = {2, 2, 1};
  NN nn = nn_alloc(arch, ARRAY_LEN(arch));
  nn_rand(nn, 1, 9);
  NN_PRINT(nn);
  return 0;
}

