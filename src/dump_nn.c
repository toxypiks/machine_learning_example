#define NN_IMPLEMENTATION
#define OLIVEC_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include "nn.h"
#include "olive.c"
#include "stb_image_write.h"

#define IMG_WIDTH 800
#define IMG_HEIGHT 800

uint32_t img_pixels[IMG_WIDTH*IMG_HEIGHT];

int main (void)
{
  size_t arch[] = {2, 2, 1};
  size_t arch_count = ARRAY_LEN(arch);
    NN nn = nn_alloc(arch, arch_count);
  nn_rand(nn, 0, 1);
  NN_PRINT(nn);

  uint32_t neuron_color = 0xFF0000FF;
  uint32_t background_color = 0xFF181818;
  Olivec_Canvas img = olivec_canvas(img_pixels, IMG_WIDTH, IMG_HEIGHT, IMG_WIDTH);
  olivec_fill(img, background_color);

  int neuron_radius = 25;
  int layer_border_vpad = 50;
  int layer_border_hpad = 50;
  int nn_width = img.width - 2*layer_border_hpad;
  int layer_hpad = nn_width / arch_count;
  for (size_t j = 0; j < arch_count; ++j) {
    size_t layer_count = arch[j];
    int nn_height = img.height - 2*layer_border_vpad;
    int layer_vpad = nn_height/layer_count;
    int layer_x = img.width/2 - nn_width/2 + layer_hpad*j + layer_hpad/2;
    int layer_y = img.height/2 - nn_height/2;
    for (size_t i = 0; i < arch[0]; ++i) {
      int cx = layer_x;
      int cy = layer_y + i * layer_vpad + layer_vpad/2;
      olivec_circle(img, cx, cy, neuron_radius, neuron_color);
    }
  }

  uint32_t frame_thicc = 10;
  uint32_t frame_color = 0xFFAAAAAA;
  olivec_frame(img, 0, 0, img.width-1, img.height-1, frame_thicc, frame_color);
  const char *img_file_path = "nn.png";
  if (!stbi_write_png(img_file_path, img.width, img.height, 4, img.pixels, img.stride*sizeof(uint32_t)))
  {
    printf("ERROR: could not save file %s\n", img_file_path);
    return 1;
  }
  printf("Saved NN to %s\n", img_file_path);

  return 0;
}
