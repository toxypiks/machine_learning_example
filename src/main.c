#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
  {0, 0},
  {1, 2},
  {2, 4},
  {3, 6},
  {4, 8},
};

#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(void)
{
  // returns number from 0-1
  return (float) rand()/ (float)RAND_MAX;
}

int main() {

  //seed random number generator with time
  srand(time(0));
  // create model that predicts the desired outcome of training data (number two of array entity)
  // y = x*w
  float w = rand_float() * 10.0f;

  float result = 0.0f;
  for(size_t i = 0; i < train_count; ++i) {
	float x = train[i][1];
	float y = x*w;
	float d = y - train[i][1];
	// d*d cause it amplifies errors and let result always be positive
	result += d*d;
  }
  result /= train_count;

  printf("%f\n", result);
  return 0;
}
