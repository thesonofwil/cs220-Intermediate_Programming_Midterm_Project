//Marcelo Morales
//lmoral10

#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.h"
#include <math.h>
#include "swirl.h"



void swirl (Image *img, int x_center, int y_center, int scale) {
  int x, y, dx, dy, tx, ty;
  double alpha, cos_a, sin_a;

  Pixel *pixel_arr = malloc(sizeof(Pixel) * img->rows * img->cols);

  for (int r = 0; r < img-> rows; ++r) {
    for (int c = 0; c < img->cols; ++c) {
      pixel_arr[(r * img->cols) + c].r = img->data[(r * img->cols) + c].r;
      pixel_arr[(r * img->cols) + c].g = img->data[(r * img->cols) + c].g;
      pixel_arr[(r * img->cols) + c].b = img->data[(r * img->cols) + c].b;
      img->data[(r * img->cols) + c].r = 0;
      img->data[(r * img->cols) + c].g = 0;
      img->data[(r * img->cols) + c].b = 0;

    }
  }

  for (x = 0; x < img->cols; ++x) {
    for (y = 0; y < img->rows; ++y) {
      dx = x - x_center;
      dy = y - y_center;
      alpha = sqrt(dx * dx + dy * dy) / (double) scale;
      cos_a = cos(alpha);
      sin_a = sin(alpha);
      
      tx = (int) (dx * cos_a - dy * sin_a + x_center);
      ty = (int) (dx * sin_a + dy * cos_a + y_center);

      if (tx >= 0 && ty >= 0 && tx < img->cols && ty < img-> rows) {

        img->data[(y * img->cols) + x].r = pixel_arr[(ty * img->cols) + tx].r;
        img->data[(y * img->cols) + x].g = pixel_arr[(ty * img->cols) + tx].g;
        img->data[(y * img->cols) + x].b = pixel_arr[(ty * img->cols) + tx].b;


      }
    }
  }
  free(pixel_arr);
}
