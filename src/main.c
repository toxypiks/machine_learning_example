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

float cost(float w)
{
  float result = 0.0f;
  for(size_t i = 0; i < train_count; ++i) {
	float x = train[i][0];
	float y = x*w;
	float d = y - train[i][1];
	result += d*d;
  }
  return result /= train_count;
}

float dcost(float w)
{
  float result = 0.0f;
  size_t n = train_count;
  for (size_t i = 0; i < n; ++i) {
	float x = train[i][0];
	float y = train[i][1];
	result += 2*(x*w - y)*x;
  }
  return result /= n;
}

int main() {

  // seed random number generator with time
  // srand(time(0));
  srand(69);
  // create model that predicts the desired outcome of training data (number two of array entity)
  // y = x*w
  float w = rand_float() * 10.0f;

  float rate = 1e-1;
  // calc easy form of derivative of function (finite difference)

  printf("cost: %f, w = %f\n", cost(w), w);
  for(size_t i = 0; i < 10; ++i)  {
// implements ability to flip flop between finite diff and derivative (if 0 -> derivative, if 1 -> finite diff)
#if 0
    float eps = 1e-3;
	float c = cost(w);
	float dw = (cost(w + eps) - c)/eps;
#else
    float dw = dcost(w);
#endif
    w -= rate * dw;
    printf("cost: %f, w = %f\n", cost(w), w);
 }

 printf("-----------------------\n");
 printf("w: %f\n", w);
 return 0;
}
