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
  
  // pixel values can't be < 0 or > 255
  for (int i = 0; i <= img->rows * img->cols; i++) {
    img->data[i].r = img->data[i].r * (pow(2.0, val));
    img->data[i].g = img->data[i].g * (pow(2.0, val));
    img->data[i].b = img->data[i].b * (pow(2.0, val));

    // Set max value 
    if (img->data[i].r > 255) {
      img->data[i].r = 255;
    }
    
    if (img->data[i].g > 255) {
      img->data[i].g = 255;
    }

    if (img->data[i].b > 255) {
      img->data[i].b = 255;
    }
  }
}
 
int main() {
  FILE *input = fopen("building.ppm", "rb");
  Image *img = read_ppm(input);

  FILE *output = fopen("building_exposure.ppm", "wb");
  change_exposure(img, 1);
  write_ppm(output, img);

  fclose(input);
  fclose(output);
  free(img->data);
  free(img);
  return 0;
}
