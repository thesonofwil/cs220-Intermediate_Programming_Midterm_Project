// 1. exposure - change exposure of an image
// 2. a-blend - blend two images by a given ratio
// 3. zoom in - zoom in to an image
// 4. zoom out - zoom out of an image
// 5. pointilism - pointilism technique
// 6. swirl - swirl the image
// 7. blur - blur the image (smooth and soften its edges) by a specified amount
// Wilson (1, 3, 5), Anire (2, 4, 6)

// image is a 2D array (rows and columns)
// loop through each pixel and apply operator

// write a function that loops through image and returns each pixel

#include <stdio.h>
#include <stdlib.h>
#include "ppm_io.c"
#include "ppm_io.h"


// struct pixel defined in header file
// struct image deinfed in header file

// Loops through an image and returns a list of rgb values separately 
int main() {
  FILE *input = fopen("data/building.ppm", "rb");
  Image *img = read_ppm(input);

  FILE *output = fopen("building_test.ppm", "wb");
  write_ppm(output, img);

  fclose(input);
  fclose(output);
  free(img->data);
  free(img);
  return 0;
}
