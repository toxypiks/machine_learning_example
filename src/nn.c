#define NN_IMPLEMENTATION
#include <stdio.h>
#include <time.h>
#include "nn.h"

typedef struct {
  size_t count;
  Mat *ws;
  Mat *bs;
  Mat *as; // is count+1 because of input layer
} NN;

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

size_t arch[] = {2, 2, 1};
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

int main(void) {
  printf("Hello World\n");
  return 0;
}

