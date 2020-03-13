#include <stdio.h>
#include <stdlib,h>
#include "ppm_io.c"
#include "ppm_io.h"

void pointilism(Image *img) {
  int area = img->rows * img->cols;
  int targetNumber = area * 0.03; // does this need to be random?

  for (int i = 0; i < targetNumber; i++) {
    int col = rand() % img->cols + 1; // generate a random x coordinate
    int row = rand() % img->rows + 1; // generate a random y coordinate

    int radius = rand() % 5 + 1; // get a random radius [0, 5]

    
  }
}
