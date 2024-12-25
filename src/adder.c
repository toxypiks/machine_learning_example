#define NN_IMPLEMENTATION
#include "nn.h"
#include <time.h>
#include "raylib.h"

#define BITS 4

#define IMG_FACTOR 80
#define IMG_WIDTH (16*IMG_FACTOR)
#define IMG_HEIGHT (9*IMG_FACTOR)

void nn_render_raylib(NN nn)
{
  Color background_color = {0x18, 0x18, 0x18, 0xFF};
  Color low_color = {0xFF, 0x00, 0xFF, 0xFF};
  Color high_color = {0x00, 0xFF, 0x00, 0xFF};

  ClearBackground(background_color);

  int neuron_radius = 25;
  int layer_border_vpad = 50;
  int layer_border_hpad = 50;
  int nn_width = IMG_WIDTH - 2*layer_border_hpad;
  int nn_height = IMG_HEIGHT - 2*layer_border_vpad;
  int nn_x = IMG_WIDTH/2 - nn_width/2;
  int nn_y = IMG_HEIGHT/2 - nn_height/2;
  size_t arch_count = nn.count + 1;
  int layer_hpad = nn_width / arch_count;
  for (size_t l = 0; l < arch_count; ++l) {
    int layer_vpad1 = nn_height / nn.as[l].cols;
    for (size_t i = 0; i < nn.as[l].cols; ++i) {
      int cx1 = nn_x + l*layer_hpad + layer_hpad/2;
      int cy1 = nn_y + i*layer_vpad1 + layer_vpad1/2;
      if (l+1 < arch_count) {
        int layer_vpad2 = nn_height / nn.as[l+1].cols;
        for (size_t j = 0; j < nn.as[l+1].cols; ++j) {
          int cx2 = nn_x + (l+1)*layer_hpad + layer_hpad/2;
          int cy2 = nn_y + j*layer_vpad2 + layer_vpad2/2;
          high_color.a = floorf(255.f*sigmoidf(MAT_AT(nn.ws[l], j, i)));
          DrawLine(cx1, cy1, cx2, cy2, ColorAlphaBlend(low_color, high_color, WHITE));
        }
      }
      if (l > 0) {
        high_color.a = floorf(255.f*sigmoidf(MAT_AT(nn.bs[l-1], 0, i)));
        DrawCircle(cx1, cy1, neuron_radius, ColorAlphaBlend(low_color, high_color, WHITE));
      } else {
        DrawCircle(cx1, cy1, neuron_radius, GRAY);
      }
    }
  }
}

int main(void) {
  srand(time(0));
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
    for (size_t j = 0; j < BITS; ++j) {
      MAT_AT(ti, i, j) = (x>>j)&1;
      MAT_AT(ti, i, j + BITS) = (y>>j)&1;
      MAT_AT(to, i, j) = (z>>j)&1;
      }
    MAT_AT(to, i, BITS) = z >= n;
    }

  size_t arch[] = {2*BITS, 4*BITS, BITS + 1};
  NN nn = nn_alloc(arch, ARRAY_LEN(arch));
  NN g = nn_alloc(arch, ARRAY_LEN(arch));
  nn_rand(nn, 0, 1);
  // NN_PRINT(nn);

  float rate = 1;

  InitWindow(IMG_WIDTH, IMG_HEIGHT, "adder");
  SetTargetFPS(60);

  size_t i = 0;
  while(!WindowShouldClose()) {
    if (i < 5000) {
      nn_backprop(nn, g, ti, to);
      nn_apply_finite_diff(nn, g, rate);
      i += 1;
      printf("c = %f\n", nn_cost(nn, ti, to));
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    nn_render_raylib(nn);
    EndDrawing();
  }
  size_t fails = 0;
  for (size_t x = 0; x < n; ++x) {
    for (size_t y = 0; y < n; ++y) {
      size_t z = x + y;
      for (size_t j = 0; j < BITS; ++j) {
        MAT_AT(NN_INPUT(nn), 0, j) = (x>>j)&1;
        MAT_AT(NN_INPUT(nn), 0, j + BITS) = (y>>j)&1;
      }
      nn_forward(nn);
      if (MAT_AT(NN_OUTPUT(nn), 0, BITS) > 0.5f) {
        if (z < n) {
          printf("%zu + %zu = (OVERFLOW<>%zu)\n", x, y, z);
          fails += 1;
        }
      } else {
        size_t a = 0;
        for (size_t j = 0; j < BITS; ++j) {
          size_t bit = MAT_AT(NN_OUTPUT(nn), 0, j) > 0.5f;
          a |= bit<<j;
        }
        if (z != a) {
          printf("%zu + %zu = (%zu<>%zu)\n", x, y, z, a);
          fails += 1;
        }
      }
    }
  }
  if (fails == 0) printf("OK\n");
  return 0;
}
