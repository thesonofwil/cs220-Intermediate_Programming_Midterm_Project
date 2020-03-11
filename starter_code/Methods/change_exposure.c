#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppm_io.c"
#include "ppm_io.h"
 
 
// struct pixel defined in header file
// struct image deinfed in header file
// Loops through an image and returns a list of rgb values separately
//int get_pixel(FILE* image, int x, int y) {

// Shift the exposure of the image by a factor of val
void change_exposure(Image *img, float val) {
  int factor = pow(2.0, val);

  // Multiply rgb values by factor 
  // Pixel values can't be < 0 or > 255, so set
  // to 255 if either happens.
  // Note: int * unsigned char yields an int
  for (int i = 0; i <= img->rows * img->cols; i++) {
    if (img->data[i].r * factor > 255 || img->data[i].r * factor < 0) {
      img->data[i].r = 255;
    } else {
      img->data[i].r = img->data[i].r * factor;
    }

    if (img->data[i].g * factor > 255 || img->data[i].g * factor < 0) {
      img->data[i].g = 255;
    } else {
      img->data[i].g = img->data[i].g * factor;
    }

    if (img->data[i].b * factor > 255 || img->data[i].b * factor < 0) {
      img->data[i].b = 255;
    } else {
      img->data[i].b = img->data[i].b * factor;
    }
  }
}

// Test change_exposure() 
int main() {
  FILE *input = fopen("building.ppm", "rb");
  Image *img = read_ppm(input);

  FILE *output = fopen("building_test.ppm", "wb");
  change_exposure(img, 2);
  write_ppm(output, img);

  fclose(input);
  fclose(output);
  free(img->data);
  free(img);
  return 0;
}
