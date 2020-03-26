#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "change_exposure.h"
 
// Shift the exposure of the image by a factor of val
void change_exposure(Image *img, float val) {
  if (val < -3 || val > 3) {
    fprintf(stderr, "EV value must be between -3 and 3. \n");
    exit(6);
  }

  float factor = pow(2.0, val);
 
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
