#define NN_IMPLEMENTATION
#define OLIVEC_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include "olive.c"
#include "stb_image_write.h"
#include <time.h>
#include "nn.h"

#define IMG_WIDTH 800
#define IMG_HEIGHT 800

uint32_t img_pixels[IMG_WIDTH*IMG_HEIGHT];

float td[] = {
  0, 0, 0,
  0, 1, 1,
  1, 0, 1,
  1, 1, 1,
};

void nn_render(Olivec_Canvas img, NN nn)
{
  uint32_t background_color = 0xFF181818;
  uint32_t low_color = 0x00FF00FF;
  uint32_t high_color = 0x0000FF00;
  olivec_fill(img, background_color);

  int neuron_radius = 25;
  int layer_border_vpad = 50;
  int layer_border_hpad = 50;
  int nn_width = img.width - 2*layer_border_hpad;
  int nn_height = img.height - 2*layer_border_vpad;
  int nn_x = img.width/2 - nn_width/2;
  int nn_y = img.height/2 - nn_height/2;
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
          uint32_t alpha = floorf(255.f*sigmoidf(MAT_AT(nn.ws[l], j, i)));
          uint32_t connection_color = 0xFF000000|low_color;
          olivec_blend_color(&connection_color, (alpha<<(8*3))|high_color);
          olivec_line(img, cx1, cy1, cx2, cy2, connection_color);
        }
      }
      if (l > 0) {
        uint32_t alpha = floorf(255.f*sigmoidf(MAT_AT(nn.bs[l-1], 0, i)));
        uint32_t neuron_color = 0xFF000000|low_color;
        olivec_blend_color(&neuron_color, (alpha<<(8*3))|high_color);
        olivec_circle(img, cx1, cy1, neuron_radius, neuron_color);
      } else {
        olivec_circle(img, cx1, cy1, neuron_radius, 0xFFAAAAAA);
      }
    }
  }
}

int main(void)
{
  srand(time(0));

  size_t stride = 3;
  // create submatrix out of columns td
  size_t n = 4;

  Mat ti = {
    .rows = n,
    .cols = 2,
    .stride = stride,
    .es = td,
  };

  Mat to = {
    .rows = n,
    .cols = 1,
    .stride = stride,
    .es = td  + 2,
  };

  size_t arch[] = {2, 2, 1};
  NN nn = nn_alloc(arch, ARRAY_LEN(arch));
  NN g = nn_alloc(arch, ARRAY_LEN(arch));
  nn_rand(nn, 0, 1);

  float rate = 1;

  printf("cost = %f\n", nn_cost(nn, ti, to));
  for (size_t i = 0; i < 5000; ++i) {
#if 0
    float eps = 1e-1;
    nn_finite_diff(nn, g, eps, ti, to);
#else
    nn_backprop(nn, g, ti, to);
#endif
    nn_apply_finite_diff(nn, g, rate);
    if(i%100 == 0) {
      printf("cost = %f\n", nn_cost(nn, ti, to));
      Olivec_Canvas img = olivec_canvas(img_pixels, IMG_WIDTH, IMG_HEIGHT, IMG_WIDTH);
      nn_render(img, nn);
      char img_file_path[256];
      snprintf(img_file_path, sizeof(img_file_path), "../out/xor-%03zu.png", i);
      if (!stbi_write_png(img_file_path, img.width, img.height, 4, img.pixels, img.stride*sizeof(uint32_t)))
      {
        printf("ERROR: could not save file %s\n", img_file_path);
        return 1;
      }
      printf("Saved NN to %s\n", img_file_path);
    }
  }

  NN_PRINT(nn);

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      MAT_AT(NN_INPUT(nn), 0, 0) = i;
      MAT_AT(NN_INPUT(nn), 0, 1) = j;
      nn_forward(nn);
      printf("%zu ^ %zu = %f\n", i, j, MAT_AT(NN_OUTPUT(nn), 0, 0));
    }
  }
  return 0;
}
