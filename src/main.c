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

float cost(float w, float b)
{
  float result = 0.0f;
  for(size_t i = 0; i < train_count; ++i) {
	float x = train[i][0];
	//model (y = x*w) of single neuron with single connection, whereas w = weight plus bias b
	float y = x*w + b;
	float d = y - train[i][1];
	// d*d cause it amplifies errors and let result always be positive
	result += d*d;
  }
  return result /= train_count;
}


int main() {

  //seed random number generator with time
  srand(time(0));
  // create model that predicts the desired outcome of training data (number two of array entity)
  // y = x*w
  float w = rand_float() * 10.0f;
  float b = rand_float() * 5.0f;

  float eps = 1e-3;
  float rate = 1e-3;
  //calc easy form of derivative of function (finite difference)

  for(size_t i = 0; i < 500; ++i)  {
   float c = cost(w, b);
   float dw = (cost(w + eps, b) - c)/eps;
   float db = (cost(w, eps + b) - c)/eps;
   w -= rate * dw;
   b -= rate * db;
   printf("cost: %f, w = %f, b = %f\n", cost(w, b), w, b);
  }

  printf("-----------------------\n");
  printf("w: %f, b: %f\n", w, b);
  return 0;
}
